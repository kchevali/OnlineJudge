class Node:
    def __init__(self, val):
        self.val = val
        self.next = None
        self.prev = None


class Linked:
    def __init__(self):
        self.head = None
        self.tail = None

    def push_front(self, val):
        node = Node(val)
        if self.head == None:
            self.head = node
            self.tail = node
        else:
            self.head.prev = node
            node.next = self.head
            self.head = node

    def push_back(self, val):
        node = Node(val)
        if self.tail == None:
            self.head = node
            self.tail = node
        else:
            self.tail.next = node
            node.prev = self.tail
            self.tail = node

    def peek_front(self):
        return self.head.val

    def peek_back(self):
        return self.tail.val

    def pop_front(self):
        if self.head == None:
            return None
        val = self.head.val
        self.head = self.head.next
        if self.head == None:
            self.tail = None
        else:
            self.head.prev = None
        return val

    def pop_back(self):
        if self.head == None:
            return None
        val = self.tail.val
        self.tail = self.tail.prev
        if self.tail == None:
            self.head = None
        else:
            self.tail.next = None
        return val

    def is_empty(self):
        return self.head == None

    def to_string_front(self):
        s = "[ "
        x = self.head
        while(not x == None):
            s += str(x.val) + ("" if x.next == None else ", ")
            x = x.next
        return s + " ]"

    def to_string_back(self):
        s = "[ "
        x = self.tail
        while(not x == None):
            s += str(x.val) + ("" if x.prev == None else ", ")
            x = x.prev
        return s + " ]"


if __name__ == '__main__':
    link = Linked()
    link.push_front(2)
    link.push_front(1)
    link.push_back(3)
    print("Popped:", link.pop_front())
    print("Popped:", link.pop_back())
    print("Popped:", link.pop_front())
    link.push_front(10)
    link.push_front(9)
    link.push_back(100)
    print(link.to_string_front())
    print(link.to_string_back())
