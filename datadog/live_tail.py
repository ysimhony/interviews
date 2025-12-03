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

def get_query_ids(log_str: str, queries_db: list[tuple[str, int]])->list[str]:
    result = []

    for i in range(len(queries_db)): # N * (M + M + K + K)
        entry_words = queries_db[i][0].split(" ")
        entry_set = set(entry_words)
        log_words = log_str.lower().split(" ")

        counter = 0

        # count the number of words appear in query entry
        for word in log_words:
            # print("debug1: ", word, entry_set)
            if word in entry_set:
                counter += 1

        # if all the words of the entry appear in the log words, then 
        # add the query id
        if counter == len(entry_words):
            result.append(str(queries_db[i][1]))

    return result

def live_tail(stream: list[str])->list[str]:

    result = []
    query_id = 1

    queries_db = []
    for i in range(len(stream)): # N* (
        if stream[i][0] == "Q":
            result.append(f"ACK: {stream[i][3:]}; ID={query_id}")
    
            # store the query string and its query id
            queries_db.append((stream[i][3:].lower(), query_id))
            query_id += 1
        if stream[i][0] == "L":
            query_ids = get_query_ids(stream[i][3:], queries_db)
            query_ids_str = ",".join(query_ids)
            # print(query_ids_str)
            if query_ids_str != "":
                result.append(f"M: {stream[i][3:]}; Q={query_ids_str}")


    return result

#time complexity
# stream size = N
# stream entry num of words(average) = M
# log num of words = K
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
        exit(2)

