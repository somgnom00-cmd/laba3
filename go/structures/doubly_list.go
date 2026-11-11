package structures

import "fmt"

type doubleNode struct {
	value string
	prev  *doubleNode
	next  *doubleNode
}

type DoublyList struct {
	head *doubleNode
	tail *doubleNode
	size int
}

func NewDoublyList() *DoublyList                          { return &DoublyList{} }
func (l *DoublyList) Type() string                        { return "DoublyList" }
func (l *DoublyList) Size() int                           { return l.size }
func (l *DoublyList) Clear()                              { l.head, l.tail, l.size = nil, nil, 0 }
func (l *DoublyList) appendSerialized(value string) error { l.PushBack(value); return nil }

func (l *DoublyList) PushFront(value string) {
	added := &doubleNode{value: value, next: l.head}
	if l.head != nil {
		l.head.prev = added
	} else {
		l.tail = added
	}
	l.head = added
	l.size++
}

func (l *DoublyList) PushBack(value string) {
	added := &doubleNode{value: value, prev: l.tail}
	if l.tail != nil {
		l.tail.next = added
	} else {
		l.head = added
	}
	l.tail = added
	l.size++
}

func (l *DoublyList) nodeAt(index int) (*doubleNode, error) {
	if index < 0 || index >= l.size {
		return nil, fmt.Errorf("list index out of range")
	}
	if index < l.size/2 {
		node := l.head
		for i := 0; i < index; i++ {
			node = node.next
		}
		return node, nil
	}
	node := l.tail
	for i := l.size - 1; i > index; i-- {
		node = node.prev
	}
	return node, nil
}

func (l *DoublyList) Insert(index int, value string) error {
	if index < 0 || index > l.size {
		return fmt.Errorf("list index out of range")
	}
	if index == 0 {
		l.PushFront(value)
		return nil
	}
	if index == l.size {
		l.PushBack(value)
		return nil
	}
	current, _ := l.nodeAt(index)
	added := &doubleNode{value: value, prev: current.prev, next: current}
	current.prev.next = added
	current.prev = added
	l.size++
	return nil
}

func (l *DoublyList) Erase(index int) error {
	node, err := l.nodeAt(index)
	if err != nil {
		return err
	}
	if node.prev != nil {
		node.prev.next = node.next
	} else {
		l.head = node.next
	}
	if node.next != nil {
		node.next.prev = node.prev
	} else {
		l.tail = node.prev
	}
	l.size--
	return nil
}

func (l *DoublyList) Values() []string {
	result := make([]string, 0, l.size)
	for node := l.head; node != nil; node = node.next {
		result = append(result, node.value)
	}
	return result
}

func (l *DoublyList) ReverseValues() []string {
	result := make([]string, 0, l.size)
	for node := l.tail; node != nil; node = node.prev {
		result = append(result, node.value)
	}
	return result
}
