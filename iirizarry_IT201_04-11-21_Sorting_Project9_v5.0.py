"""
    Program: iirizarry_IT201_04-11-21_Sorting_Project9_v5.0.py
    Author(s): Israel Irizarry
    Email: iirizarry33 at students.cumberland.edu
    Date: March 17, 2021
    Class - Data Structures and Algorithms
    Professor - Dr. Nichols
    ***Honor Code***
    
    Objective: Display the time differences of different sorting algorithms at different list lengths.
    
    Version 1.0 - Created list creation function, python sort() timer, and average calculation function.
    Version 2.0 - Created function for insertion sorting.
    Version 3.0 - Created function for merge sort sorting.
    Version 4.0 - Created function for quick sort sorting.
    Version 5.0 - Organized data for 10, 100, and 1000 element lists and displayed the tables to the screen.

    
    Algorithm:
        1. Create a function to create random list that are 10 elements long 1000 times and put them into another list.
        2. Sort the lists through python's sort() method.
        3. Time the process of each list to sort and find the average time and display to screen.
        4. Repeat 2 and 3 but with the insertion algorithm (algorthm in book).
        5. Repeat 2 and 3 but with the merge sort algorithm (algorithm in book).
        6. Repeat 2 and 3 but with the quicksort sort algorithm (algorithm in book).
        7. Repat 1-6 with 100 and 1000 elements.
        8. Display the tables of times to the screen.
        
    ***Credits***
        TEXTBOOK: The textbook was used to get the meger sort algorithm code.
        WEBSITE: https://www.geeksforgeeks.org/python-list-copy-method/ was used to learn the deepcopy() function.
        

    System Information:
        OS: Windows 10 Home X64
        Version: 10,0,19041 Build 19041
        CPU: Intel Celeron 1.10GHz
        RAM: 4GB
        
    Run via command line:

        python C:Users/israe/Desktop/Programming/iirizarry_IT201_04-11-21_Sorting_Project9_v5.0.py

    Output:
    
    Algorithm      N:      nList:      Average:
    TempSort        10        1000        0.000000000000
    Insertion       10        1000        0.000031202793
    Merge           10        1000        0.000031240463
    Quick           10        1000        0.000015619278


    Algorithm      N:      nList:      Average:
    TempSort        100        1000        0.000015619755
    Insertion       100        1000        0.001780713558
    Merge           100        1000        0.000321330309
    Quick           100        1000        0.000218679905


    Algorithm      N:      nList:      Average:
    TempSort        1000        1000        0.000140583754
    Insertion       1000        1000        0.242702439308
    Merge           1000        1000        0.005973431587
    Quick           1000        1000        0.003922331333
"""
#----------------------------------------------------------------------------------------|
#Imports Libraries.
import time
import sys
import random
import copy

def main():
    '''
        Sets global time and number of elements in each list.
    '''

    #Creates temperary time for each sorting algorithm.
    global tempTime
    tempTime = 0

    global times
    times = []

    global randAmount
    randAmount = 10

    #Sets number of elements in each random list and calls ListCreator().
    ListCreator(randAmount)
    Display()
    print("\n")
    times = []
    randAmount = 100
    ListCreator(randAmount)
    Display()
    print("\n")
    times = []
    randAmount = 1000
    ListCreator(randAmount)
    Display()
    print(" ")

    
def ListCreator(y):
    '''
        Creates a random list of 10, 100, and 1000 elements 1000 times and calls on sorting algorithms.
    '''

    #Variables.
    averageL = []
    global firstHalf
    firstHalf = []
    global firstL
    firstL = 0
    n = []
    global q
    q = []

    #Creates lists of random list.
    for j in range(0,1000):

        #Creates each list based on 10, 100, or 1000.
        for i in range(1,y+1):
            n.append(i)
        random.shuffle(n)
        q.append(n)
        n = []

    #Calls sorting algorithm functions using a copy of the list of random lists.
    tempX = copy.deepcopy(q)
    TempSort(tempX)
    tempX = copy.deepcopy(q)
    Insertion(tempX)
    tempX = copy.deepcopy(q)

    #Times merge sort and calls average.
    for i in tempX:
        start = time.time()
        Merge(i)
        end = time.time()
        tempTime = end-start
        averageL.append(tempTime)
    Average(averageL)
    averageL = []
    tempX = copy.deepcopy(q)

    #Calls quick sort algorithm and calls average.
    for i in tempX:
        start = time.time()
        QuickSort(i,0,len(i)-1)
        end = time.time()
        tempTime = end-start
        averageL.append(tempTime)
    Average(averageL)
    
def TempSort(x):
    '''
        Sorts the lists (x) using pyhton's built in sorting.
    '''

    #List of times per list sort.
    averageL =[]

    #For every random list in x it sorts the list, times it, and appends the time to the time holder.
    for i in x:
        start = time.time()
        
        i.sort()
        
        end = time.time()
        
        tempTime = end-start
        averageL.append(tempTime)

    #Uses all the times in averageL to call Average.
    Average(averageL)

def Insertion(x):
    '''
        Sorts x based on the insertion algorithm.
    '''

    #Variables used.
    averageL =[]

    #Variables used.
    tempList = 0
    tempPlace = 1

    #For every element in x, it checks the next one and inserts the element in the correct place if needed.
    for j in range(len(x)):

        #Starts timer.
        start = time.time()

        #Sorts each random list.
        for i in range(len(x[j])):
            while x[j][i-tempPlace] >= x[j][i-tempPlace+1] and x[j][i-tempPlace] != x[j][-1]:
                tempList = x[j][i-tempPlace+1]
                x[j][i-tempPlace+1] = x[j][i-tempPlace]
                x[j][i-tempPlace] = tempList
                tempPlace += 1
            tempPlace = 1

        #Ends timer.
        end = time.time()
        
        tempTime = end-start
        averageL.append(tempTime)

    #Calls Average to find average time.
    Average(averageL)

def Merge(x):
    '''
        Sorts x based on the merge sort algorithm.
        ***CODE USED FROM BOOK BUT WAS MODIFIED TO FIT PROGRAM AND TIMER.
    '''

    #Calls global algorithms.
    global firstL
    global firstHalf

    #For the length of x it splits each list in 2 over and over and sorts
    #Each piece and combines the list.
    if len(x)>1:
        mid = len(x)//2
        left = x[:mid]
        right = x[mid:]
        Merge(left)
        Merge(right)
        i = j = k = 0

        #Splits the list over and over until it cant be split and sorts them.
        while i<len(left) and j < len(right):
            if left[i]<right[j]:
                x[k]=left[i]
                i+=1
            else:
                x[k] = right[j]
                j+= 1
            k+=1

        #Sorts left side.
        while i < len(left):
            x[k] = left[i]
            i+=1
            k+=1

        #Sorts right side.
        while j < len(right):
            x[k] = right[j]
            j+=1
            k+=1

        #CODE NOT FROM BOOK. This combines hte left and right list.
        if len(x) == len(x)/2 and firstL == 0:
            firstL+=1
            for i in x:
                firstHalf.append(i)

def QuickSort(x,low,high):
    '''
        Begins quick sort algorithm by setting the pivot if low < high.
        ***CODE USED FROM BOOK.
    '''
    
    if low < high:
        pivot = Partition(x,low,high)
        QuickSort(x,low,pivot-1)
        QuickSort(x,pivot+1,high)
def Partition(x,low,high):
    '''
        Swaps pivot and high to sort from pivot.
    '''

    #Calls swap() to set new pivot and sort.
    pivot = low
    swap(x,pivot,high)
    
    for i in range(low,high):
        if x[i] <= x[high]:
            swap(x,i,low)
            low+= 1
    swap(x,low,high)
    return low
def swap(x,y,z):
    '''
        Swaps y and z.
    '''

    #Variables to swap.
    temp = x[y]
    x[y] = x[z]
    x[z] = temp

def Average(x):
    '''
        Calculates the average of time for each sorting algorithm.
    '''

    #Resets average for every sorting algotithm
    average = 0

    #Calculates the average.
    for i in x:
        average += float(i)

    #Calculates average, formats it, and prints it.
    average = average/int(len(x))
    tempTime = "{:.12f}".format(average)
    times.append(tempTime)


def Display():
    '''
        Formats the times and number of elements into 3 tables.
    '''
    
    print("Algorithm","     N:","     nList:","     Average:")
    print("TempSort","      ",randAmount,"       1000","      ",times[0])
    print("Insertion","     ",randAmount,"       1000","      ",times[1])
    print("Merge","         ",randAmount,"       1000","      ",times[2])
    print("Quick","         ",randAmount,"       1000","      ",times[3])

#Calls main().
main()
