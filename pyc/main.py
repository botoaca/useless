from ctypes import POINTER, c_int, CDLL
import time
import random

c_sort = CDLL(".\c_sort.so")

def generate_random_array(length, max_val):
    return [random.randint(0, max_val) for _ in range(length)]

def py_bubble_sort(arr, arr_len):
    for i in range(arr_len):
        for j in range(arr_len - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

# def ctypes_arr_to_list(arr, len_arr):
#     return [arr[i] for i in range(len_arr)]

def list_to_ctypes_arr(arr):
    return (c_int * len(arr))(*arr)

# arr = [1, 43, 5, 2, 7, 23, 9, -1, 3] # [-1, 1, 2, 3, 5, 7, 9, 23, 43]
arr = generate_random_array(100000, 1000)
arr_len = len(arr)

def run_py_test():
    start = time.perf_counter()
    py_sorted_arr = py_bubble_sort(arr, arr_len)
    end = time.perf_counter()
    return ((end - start), py_sorted_arr)

def run_c_test():
    start = time.perf_counter()
    Call = c_sort.bubble_sort
    Call.argtypes = [POINTER(c_int), c_int]
    Call.restype = POINTER(c_int)
    c_sorted_arr = Call(list_to_ctypes_arr(arr), arr_len)[:arr_len]
    end = time.perf_counter()
    return ((end - start), c_sorted_arr)

def main():
    print("\n\nRunning Python test...")
    py_time, py_sorted_arr = run_py_test()
    print(f"Bubble sort, Python: {py_time:0.4f}")
    # print(f"Sorted array: {py_sorted_arr}\n")
    
    print("Running C test...")
    c_time, c_sorted_arr = run_c_test()
    print(f"Bubble sort, C: {c_time:0.4f}")
    # print(f"Sorted array: {c_sorted_arr}\n\n")

if __name__ == "__main__":
    main()