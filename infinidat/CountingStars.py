import heapq


def CountingStars(stars_indexes_arr: list[list[int]])->None:
    heap = []
    m = len(stars_indexes_arr)
    n = len(stars_indexes_arr[0])
    for i in range(m):
        heapq.heappush(heap, (stars_indexes_arr[i][0], i, 0))

    prev = None
    count = 1
    while heap:
#        print(heap)
        val, row, col = heapq.heappop(heap)

        if col + 1 < n:
            heapq.heappush(heap, (stars_indexes_arr[row][col+1], row, col+1))

        if val != prev:
            if count % 2 == 1 and prev != None :
                print(prev)
            count = 1
        else:
            count += 1

        prev = val

    if count % 2 == 1:
        print(val)
    return



stars_indexes_arr = [[2, 5, 6], [0, 2, 3], [6, 10, 11]]
CountingStars(stars_indexes_arr)
