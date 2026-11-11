package structures

import "fmt"

type Queue struct {
	head *singleNode
	tail *singleNode
	size int
}

func NewQueue() *Queue                               { return &Queue{} }
func (q *Queue) Type() string                        { return "Queue" }
func (q *Queue) Size() int                           { return q.size }
func (q *Queue) Clear()                              { q.head, q.tail, q.size = nil, nil, 0 }
func (q *Queue) appendSerialized(value string) error { q.Push(value); return nil }

func (q *Queue) Push(value string) {
	added := &singleNode{value: value}
	if q.tail != nil {
		q.tail.next = added
	} else {
		q.head = added
	}
	q.tail = added
	q.size++
}

func (q *Queue) Front() (string, error) {
	if q.head == nil {
		return "", fmt.Errorf("queue is empty")
	}
	return q.head.value, nil
}

func (q *Queue) Pop() (string, error) {
	value, err := q.Front()
	if err != nil {
		return "", err
	}
	q.head = q.head.next
	q.size--
	if q.head == nil {
		q.tail = nil
	}
	return value, nil
}

func (q *Queue) Values() []string {
	result := make([]string, 0, q.size)
	for node := q.head; node != nil; node = node.next {
		result = append(result, node.value)
	}
	return result
}
