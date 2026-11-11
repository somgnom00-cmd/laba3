package structures

import "fmt"

type Array struct {
	data []string
}

func NewArray() *Array                               { return &Array{} }
func (a *Array) Type() string                        { return "Array" }
func (a *Array) Size() int                           { return len(a.data) }
func (a *Array) Values() []string                    { return append([]string(nil), a.data...) }
func (a *Array) Clear()                              { a.data = nil }
func (a *Array) PushBack(value string)               { a.data = append(a.data, value) }
func (a *Array) appendSerialized(value string) error { a.PushBack(value); return nil }

func (a *Array) Insert(index int, value string) error {
	if index < 0 || index > len(a.data) {
		return fmt.Errorf("array index out of range")
	}
	a.data = append(a.data, "")
	copy(a.data[index+1:], a.data[index:])
	a.data[index] = value
	return nil
}

func (a *Array) Erase(index int) error {
	if index < 0 || index >= len(a.data) {
		return fmt.Errorf("array index out of range")
	}
	copy(a.data[index:], a.data[index+1:])
	a.data = a.data[:len(a.data)-1]
	return nil
}

func (a *Array) At(index int) (string, error) {
	if index < 0 || index >= len(a.data) {
		return "", fmt.Errorf("array index out of range")
	}
	return a.data[index], nil
}

func (a *Array) Find(value string) int {
	for i, stored := range a.data {
		if stored == value {
			return i
		}
	}
	return -1
}
