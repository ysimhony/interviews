from typing import Dict

livetail_stream = [
  "Q: database",
  "Q: Stacktrace",
  "Q: loading failed",
  "L: Database service started",
  "Q: snapshot loading",
  "Q: fail",
  "L: Started processing events",
  "L: Loading main DB snapshot",
  "L: Loading snapshot failed no stacktrace available",
]

livetail_output = [
  "ACK: database; ID=1",
  "ACK: Stacktrace; ID=2",
  "ACK: loading failed; ID=3",
  "M: Database service started; Q=1",
  "ACK: snapshot loading; ID=4",
  "ACK: fail; ID=5",
  "M: Loading main DB snapshot; Q=4",
  "M: Loading snapshot failed no stacktrace available; Q=2,3,4",
]

def get_query_ids(log_str: str, words2listOfQueryIds: Dict[str, list[int]], queries_db: Dict[int, str])->list[str]:

    result = []

    log_words = log_str.lower().split(" ")
    streamIdCount = {}

    # print("words2listOfQueryIds: ", words2listOfQueryIds)

    # walk through all the words of L, and create hash map which maps between each
    # query id Q and the number of words appear in that query
    for word in log_words:
        if word not in words2listOfQueryIds:
            continue
        queries_ids_list = words2listOfQueryIds[word]
        for query_id in queries_ids_list:
            if query_id not in streamIdCount:
                streamIdCount[query_id] = 1
            else:
                streamIdCount[query_id] += 1

    # print("log_str: ", log_str, streamIdCount)

    # add only the query ids that all of their words appear in L
    for key in streamIdCount.keys():
        stream_str = queries_db[key]
        stream_str_words = stream_str.split(" ")
        # print("yacov: ", len(stream_str_words), streamIdCount[key])
        if len(stream_str_words) == streamIdCount[key]:
            result.append(str(key))
    # print("result: ", result)
    result.sort()
    return result

def live_tail(stream: list[str])->list[str]:

    result = []
    query_id = 1

    queries_db_id2query = {}
    words2listOfQueryIds = {}
    for i in range(len(stream)):
        if stream[i][0] == "Q":
            result.append(f"ACK: {stream[i][3:]}; ID={query_id}")

            query_str = stream[i][3:]
            query_str_words = query_str.lower().split(" ")

            for word in query_str_words:
                if word not in words2listOfQueryIds:
                    words2listOfQueryIds[word] = []
                words2listOfQueryIds[word].append(query_id)

            queries_db_id2query[query_id] = stream[i][3:]

            query_id += 1
        if stream[i][0] == "L":
            query_ids = get_query_ids(stream[i][3:].lower(), words2listOfQueryIds, queries_db_id2query)
            query_ids_str = ",".join(query_ids)
            # print(query_ids_str)
            if query_ids_str != "":
                result.append(f"M: {stream[i][3:]}; Q={query_ids_str}")


    return result

output = live_tail(livetail_stream)
for s in output:
    print(s)

print()
if len(output) != len(livetail_output):
    print(f"Error in output list length expected: {len(livetail_output)} actual: {len(output)}")
    exit(1)

for i in range(len(output)):
    if output[i] != livetail_output[i]:
        print(f"Error in output entry in index {i}:")
        print(f"Expected entry: {livetail_output[i]}")
        print(f"Actual entry: {output[i]}")


