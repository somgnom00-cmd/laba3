package structures

import "fmt"

type SinglyList struct {
	head *singleNode
	tail *singleNode
	size int
}

func NewSinglyList() *SinglyList                          { return &SinglyList{} }
func (l *SinglyList) Type() string                        { return "SinglyList" }
func (l *SinglyList) Size() int                           { return l.size }
func (l *SinglyList) Clear()                              { l.head, l.tail, l.size = nil, nil, 0 }
func (l *SinglyList) appendSerialized(value string) error { l.PushBack(value); return nil }

func (l *SinglyList) PushFront(value string) {
	added := &singleNode{value: value, next: l.head}
	l.head = added
	if l.tail == nil {
		l.tail = added
	}
	l.size++
}

func (l *SinglyList) PushBack(value string) {
	added := &singleNode{value: value}
	if l.tail != nil {
		l.tail.next = added
	} else {
		l.head = added
	}
	l.tail = added
	l.size++
}

func (l *SinglyList) nodeAt(index int) (*singleNode, error) {
	if index < 0 || index >= l.size {
		return nil, fmt.Errorf("list index out of range")
	}
	node := l.head
	for i := 0; i < index; i++ {
		node = node.next
	}
	return node, nil
}

func (l *SinglyList) Insert(index int, value string) error {
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
	before, _ := l.nodeAt(index - 1)
	before.next = &singleNode{value: value, next: before.next}
	l.size++
	return nil
}

func (l *SinglyList) Erase(index int) error {
	if index < 0 || index >= l.size {
		return fmt.Errorf("list index out of range")
	}
	if index == 0 {
		l.head = l.head.next
		l.size--
		if l.size == 0 {
			l.tail = nil
		}
		return nil
	}
	before, _ := l.nodeAt(index - 1)
	if before.next == l.tail {
		l.tail = before
	}
	before.next = before.next.next
	l.size--
	return nil
}

func (l *SinglyList) Values() []string {
	result := make([]string, 0, l.size)
	for node := l.head; node != nil; node = node.next {
		result = append(result, node.value)
	}
	return result
}
