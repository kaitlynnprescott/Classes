'''
Created on Feb 5, 2018
@author: Brian Borowski
Solution to HackerRank -> Data Structures -> Queues ->
            Queue using Two Stacks
'''
class Stack(object):
    def __init__(self):
        self.items = []

    def is_empty(self):
        return self.items == []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        return self.items.pop()

    def peek(self):
        return self.items[len(self.items) - 1]

    def size(self):
        return len(self.items)

class Queue(object):
    def __init__(self):
        self.stack1 = Stack()
        self.stack2 = Stack()

    def enqueue(self, item):
        self.stack1.push(item)

    def dequeue(self):
        if self.stack2.is_empty():
            while not self.stack1.is_empty():
                self.stack2.push(self.stack1.pop())
        if not self.stack2.is_empty():
            return self.stack2.pop()
        return None

    def front(self):
        if self.stack2.is_empty():
            while not self.stack1.is_empty():
                self.stack2.push(self.stack1.pop())
        if not self.stack2.is_empty():
            return self.stack2.peek()
        return None

if __name__ == '__main__':
    q = Queue()
    for _ in range(int(input())):
        line = input().split()
        query_type = line[0]
        if query_type == '1':
            q.enqueue(int(line[1]))
        elif query_type == '2':
            q.dequeue()
        else:
            print(q.front())
