package structures

type treeNode struct {
	value       string
	left, right *treeNode
}

type CompleteBinaryTree struct {
	root *treeNode
	size int
}

func NewCompleteBinaryTree() *CompleteBinaryTree                  { return &CompleteBinaryTree{} }
func (t *CompleteBinaryTree) Type() string                        { return "CompleteBinaryTree" }
func (t *CompleteBinaryTree) Size() int                           { return t.size }
func (t *CompleteBinaryTree) Clear()                              { t.root, t.size = nil, 0 }
func (t *CompleteBinaryTree) appendSerialized(value string) error { t.Insert(value); return nil }

func (t *CompleteBinaryTree) Insert(value string) {
	added := &treeNode{value: value}
	if t.root == nil {
		t.root = added
		t.size = 1
		return
	}
	pending := []*treeNode{t.root}
	for len(pending) > 0 {
		current := pending[0]
		pending = pending[1:]
		if current.left == nil {
			current.left = added
			t.size++
			return
		}
		if current.right == nil {
			current.right = added
			t.size++
			return
		}
		pending = append(pending, current.left, current.right)
	}
}

func (t *CompleteBinaryTree) Values() []string {
	result := make([]string, 0, t.size)
	if t.root == nil {
		return result
	}
	pending := []*treeNode{t.root}
	for len(pending) > 0 {
		current := pending[0]
		pending = pending[1:]
		result = append(result, current.value)
		if current.left != nil {
			pending = append(pending, current.left)
		}
		if current.right != nil {
			pending = append(pending, current.right)
		}
	}
	return result
}

func (t *CompleteBinaryTree) Contains(value string) bool {
	for _, stored := range t.Values() {
		if stored == value {
			return true
		}
	}
	return false
}

func (t *CompleteBinaryTree) IsComplete() bool {
	if t.root == nil {
		return true
	}
	pending := []*treeNode{t.root}
	gap := false
	for len(pending) > 0 {
		current := pending[0]
		pending = pending[1:]
		if current == nil {
			gap = true
			continue
		}
		if gap {
			return false
		}
		pending = append(pending, current.left, current.right)
	}
	return true
}
