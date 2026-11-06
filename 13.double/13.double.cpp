
#include <iostream>
#include <string>
using namespace std;

// Завдання 1. Структура вагона
struct Vagon
{
    int number;
    int seats;
    int passengers;
};

ostream& operator<<(ostream& out, const Vagon& v)
{
    out << "Vagon: " << v.number
        << " | Seats: " << v.seats
        << " | Passengers: " << v.passengers;
    return out;
}

// Шаблонний двозв'язний список
template <typename T>
class List
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;

        Node(T value)
        {
            data = value;
            next = nullptr;
            prev = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size;

public:
    List()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // Конструктор копіювання
    List(const List& other)
    {
        head = nullptr;
        tail = nullptr;
        size = 0;

        Node* current = other.head;

        while (current != nullptr)
        {
            AddToTail(current->data);
            current = current->next;
        }
    }

    // Оператор присвоєння
    List& operator=(const List& other)
    {
        if (this != &other)
        {
            Clear();

            Node* current = other.head;

            while (current != nullptr)
            {
                AddToTail(current->data);
                current = current->next;
            }
        }

        return *this;
    }

    ~List()
    {
        Clear();
    }

    void Clear()
    {
        while (head != nullptr)
        {
            DeleteFromHead();
        }
    }

    void AddToHead(T value)
    {
        Node* temp = new Node(value);

        if (head == nullptr)
        {
            head = tail = temp;
        }
        else
        {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }

        size++;
    }

    void AddToTail(T value)
    {
        Node* temp = new Node(value);

        if (tail == nullptr)
        {
            head = tail = temp;
        }
        else
        {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }

        size++;
    }

    // Завдання 3. Видалення з голови
    void DeleteFromHead()
    {
        if (head == nullptr)
        {
            return;
        }

        Node* temp = head;
        head = head->next;

        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        else
        {
            tail = nullptr;
        }

        delete temp;
        size--;
    }

    void DeleteFromTail()
    {
        if (tail == nullptr)
        {
            return;
        }

        Node* temp = tail;
        tail = tail->prev;

        if (tail != nullptr)
        {
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;
        }

        delete temp;
        size--;
    }

    // Завдання 4. Додавання за позицією
    void AddAtPosition(T value, int position)
    {
        if (position < 0 || position > size)
        {
            cout << "Invalid position!" << endl;
            return;
        }

        if (position == 0)
        {
            AddToHead(value);
            return;
        }

        if (position == size)
        {
            AddToTail(value);
            return;
        }

        Node* current = head;

        for (int i = 0; i < position; i++)
        {
            current = current->next;
        }

        Node* temp = new Node(value);

        temp->next = current;
        temp->prev = current->prev;

        current->prev->next = temp;
        current->prev = temp;

        size++;
    }

    // Завдання 4. Видалення за позицією
    void DeleteAtPosition(int position)
    {
        if (position < 0 || position >= size)
        {
            cout << "Invalid position!" << endl;
            return;
        }

        if (position == 0)
        {
            DeleteFromHead();
            return;
        }

        if (position == size - 1)
        {
            DeleteFromTail();
            return;
        }

        Node* current = head;

        for (int i = 0; i < position; i++)
        {
            current = current->next;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;
        size--;
    }

    void Print() const
    {
        Node* current = head;

        while (current != nullptr)
        {
            cout << current->data << endl;
            current = current->next;
        }
    }

    int GetSize() const
    {
        return size;
    }
};

// Завдання 2. Клас Train
class Train
{
private:
    string model;
    int countVagons;
    List<Vagon> vagons;

public:
    // Дефолтний конструктор
    Train()
    {
        model = "Unknown";
        countVagons = 0;
    }

    // Параметризований конструктор
    Train(string model)
    {
        this->model = model;
        countVagons = 0;
    }

    // Конструктор копіювання
    Train(const Train& other)
        : model(other.model),
        countVagons(other.countVagons),
        vagons(other.vagons)
    {
    }

    void AddToHead(Vagon v)
    {
        vagons.AddToHead(v);
        countVagons++;
    }

    void AddToTail(Vagon v)
    {
        vagons.AddToTail(v);
        countVagons++;
    }

    void DeleteFromHead()
    {
        if (countVagons == 0)
        {
            cout << "Train is empty!" << endl;
            return;
        }

        vagons.DeleteFromHead();
        countVagons--;
    }

    void DeleteFromTail()
    {
        if (countVagons == 0)
        {
            cout << "Train is empty!" << endl;
            return;
        }

        vagons.DeleteFromTail();
        countVagons--;
    }

    void AddAtPosition(Vagon v, int position)
    {
        if (position < 0 || position > countVagons)
        {
            cout << "Invalid position!" << endl;
            return;
        }

        vagons.AddAtPosition(v, position);
        countVagons++;
    }

    void DeleteAtPosition(int position)
    {
        if (position < 0 || position >= countVagons)
        {
            cout << "Invalid position!" << endl;
            return;
        }

        vagons.DeleteAtPosition(position);
        countVagons--;
    }

    void Show() const
    {
        cout << "\nTrain model: " << model << endl;
        cout << "Count of vagons: " << countVagons << endl;

        if (countVagons == 0)
        {
            cout << "No vagons!" << endl;
            return;
        }

        vagons.Print();
    }
};

int main()
{
    Train train("Hyundai");
    int choice;
    int number, seats, passengers, position;

    do
    {
        cout << "\n===== TRAIN MENU =====" << endl;
        cout << "1. Add vagon to head" << endl;
        cout << "2. Add vagon to tail" << endl;
        cout << "3. Delete from head" << endl;
        cout << "4. Delete from tail" << endl;
        cout << "5. Add at position" << endl;
        cout << "6. Delete at position" << endl;
        cout << "7. Show train" << endl;
        cout << "8. Test copy constructor" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        case 2:
        case 5:
        {
            cout << "Enter vagon number: ";
            cin >> number;

            cout << "Enter seats: ";
            cin >> seats;

            cout << "Enter passengers: ";
            cin >> passengers;

            if (seats < 0 || passengers < 0 ||
                passengers > seats)
            {
                cout << "Invalid passenger data!" << endl;
                break;
            }

            Vagon v = { number, seats, passengers };

            if (choice == 1)
            {
                train.AddToHead(v);
            }
            else if (choice == 2)
            {
                train.AddToTail(v);
            }
            else
            {
                cout << "Enter position (from 0): ";
                cin >> position;
                train.AddAtPosition(v, position);
            }

            break;
        }

        case 3:
            train.DeleteFromHead();
            break;

        case 4:
            train.DeleteFromTail();
            break;

        case 6:
            cout << "Enter position (from 0): ";
            cin >> position;
            train.DeleteAtPosition(position);
            break;

        case 7:
            train.Show();
            break;

        case 8:
        {
            Train copy(train);

            cout << "\nCopied train:" << endl;
            copy.Show();
            break;
        }

        case 0:
            cout << "Exit!" << endl;
            break;

        default:
            cout << "Wrong choice!" << endl;
        }

    } while (choice != 0);

    return 0;
}
