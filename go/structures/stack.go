package structures

import "fmt"

type Stack struct {
	top  *singleNode
	size int
}

func NewStack() *Stack             { return &Stack{} }
func (s *Stack) Type() string      { return "Stack" }
func (s *Stack) Size() int         { return s.size }
func (s *Stack) Clear()            { s.top, s.size = nil, 0 }
func (s *Stack) Push(value string) { s.top = &singleNode{value: value, next: s.top}; s.size++ }

func (s *Stack) appendSerialized(value string) error {
	added := &singleNode{value: value}
	if s.top == nil {
		s.top = added
	} else {
		bottom := s.top
		for bottom.next != nil {
			bottom = bottom.next
		}
		bottom.next = added
	}
	s.size++
	return nil
}

func (s *Stack) Top() (string, error) {
	if s.top == nil {
		return "", fmt.Errorf("stack is empty")
	}
	return s.top.value, nil
}

func (s *Stack) Pop() (string, error) {
	value, err := s.Top()
	if err != nil {
		return "", err
	}
	s.top = s.top.next
	s.size--
	return value, nil
}

func (s *Stack) Values() []string {
	result := make([]string, 0, s.size)
	for node := s.top; node != nil; node = node.next {
		result = append(result, node.value)
	}
	return result
}
