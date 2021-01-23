#include <iostream>
#include <exception>

class EmptyListError final : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "The list is empty!";
    }
};

template <typename T>
struct Node {
    // Node *prev;
    Node *next;
    T data;
};

template <typename T>
class LinkedList final {
public:
    explicit LinkedList()
            : head_(nullptr)
            , tail_(nullptr)
            , size_(0) { }

    ~LinkedList() {
        while (head_ != nullptr) {
            auto *next = head_->next;
            delete head_;
            head_ = next;
        }
    }

    const auto& head() const {
        if (!head_) {
            throw EmptyListError();
        }
        return head_->data;
    }

    const auto& tail() const {
        if (!tail_) {
            throw EmptyListError();
        }
        return tail_->data;
    }

    const auto& size() const { return size_; }

    void append(T item) {
        auto* new_node = new Node<T>{nullptr, item};

        if (!head_) {
            head_ = new_node;
            tail_ = head_;
        } else {
            tail_->next = new_node;
            tail_ = new_node;
        }
    }

private:
    Node<T> *head_;
    Node<T> *tail_;
    std::size_t size_;

    template <typename U>
    friend std::ostream& operator <<(std::ostream& os, const LinkedList<U>& list);
};

template <typename T>
std::ostream& operator <<(std::ostream& os, const LinkedList<T>& list) {
    for (auto* head = list.head_; head; head = head->next) {
        os << head->data << ' ';
    }
    return os;
}

int main() {
    LinkedList<int> urmum = LinkedList<int>();
    urmum.append(69);
    urmum.append(420);
    urmum.append(1234);
    std::cout << urmum << std::endl;
}
