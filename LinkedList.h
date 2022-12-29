template<class T>
class LinkedList {
public:
    class Node {
    public:
        T val;
        Node* next;

        Node();
        Node(const T&);
    };

private:
    Node* head;

public:

    LinkedList();

    Node* begin() const;

    bool empty();

    void push_front(const T&);
    void push_back(const T&);

    void pop_front();
    void pop_back();

    void push(Node*, const T&);
    void pop(Node*);

    Node* find(const T&);

    void erase(const T&);

    template<class> friend std::ostream& operator<<(std::ostream&, const LinkedList&);

    template<class> friend LinkedList operator+(const LinkedList&, const LinkedList&);

    void sort();
};

template<class T>
typename LinkedList<T>::Node* LinkedList<T>::begin() const {
    return head->next;
}

template<class T>
LinkedList<T>::Node::Node() {
    next = nullptr;
}

template<class T>
LinkedList<T>::Node::Node(const T & val_) {
    val = val_;
    next = nullptr;
}

template<class T>
LinkedList<T>::LinkedList() {
    head = new Node();
}

template<class T>
bool LinkedList<T>::empty() {
    return !head->next;
}

template<class T>
void LinkedList<T>::push_front(const T & val) {
    Node* v = new Node(val);
    v->next = head->next;
    head->next = v;
}

template<class T>
void LinkedList<T>::push_back(const T & val) {
    Node* v = head;
    while (v->next)
        v = v->next;
    v->next = new Node(val);
}

template<class T>
void LinkedList<T>::pop_front() {
    Node* v = head->next;
    head->next = head->next->next;
    delete v;
}

template<class T>
void LinkedList<T>::pop_back() {
    Node* v = head;
    while (v->next->next)
        v = v->next;
    delete v->next;
    v->next = nullptr;
}

template<class T>
void LinkedList<T>::push(LinkedList::Node * v, const T& val) {
    Node* u = head;
    while (u->next != v)
        v = v->next;
    Node* w = new Node(val);
    w->next = u->next;
    u->next = w;
}

template<class T>
void LinkedList<T>::pop(LinkedList::Node * v) {
    Node* u = head;
    while (u->next != v)
        u = u->next;
    u->next = u->next->next;
    delete v;
}

template<class T>
typename LinkedList<T>::Node* LinkedList<T>::find(const T & val) {
    for (auto v = this->begin(); v; v = v->next)
        if (v->val == val)
            return v;
    return nullptr;
}

template<class T>
void LinkedList<T>::erase(const T & val) {
    pop(find(val));
}

template<class T>
std::ostream &operator<<(std::ostream & out, const LinkedList<T> & l) {
    for (auto v = l.begin(); v; v = v->next)
        out << v->val << " ";
    return out;
}

template<class T>
LinkedList<T> operator+(const LinkedList<T> & l1, const LinkedList<T> & l2) {
    auto ret = l1;
    for (auto v = l2.begin(); v; v = v->next)
        ret.pushBack(v->val);
    return ret;
}

template<class T>
void LinkedList<T>::sort() {
    auto h = this->begin();
    if (!h || !h->next)
        return;

    LinkedList<T> l1, l2;
    auto h1 = l1.head, h2 = l2.head;
    for (int i = 0; h; ++i) {
        if (i % 2 == 0) {
            h1->next = new typename LinkedList<T>::Node(h->val);
            h1 = h1->next;
        }
        else {
            h2->next = new typename LinkedList<T>::Node(h->val);
            h2 = h2->next;
        }
        h = h->next;
    }

    l1.sort();
    l2.sort();

    h1 = l1.begin(), h2 = l2.begin();
    h = this->begin();
    while (h1 && h2) {
        h->val = std::min(h1->val, h2->val);
        if (h1->val < h2->val)
            h1 = h1->next;
        else
            h2 = h2->next;
        h = h->next;
    }
    while (h1) {
        h->val = h1->val;
        h = h->next;
        h1 = h1->next;
    }
    while (h2) {
        h->val = h2->val;
        h = h->next;
        h2 = h2->next;
    }
}
