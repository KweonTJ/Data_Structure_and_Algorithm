#include "PolyList.h"

CPolyList::CPolyList() 
{
    head = nullptr;
    last = nullptr;
}

CPolyList::~CPolyList() 
{
    Clear();
}

void CPolyList::Clear() 
{
    NODE* curr = head;    
    while (curr != nullptr)
    {
        NODE* temp = curr;
        curr = curr->link;
        delete temp;
    }
    head = nullptr;
    last = nullptr;
}

void CPolyList::AppendTerm(int coef, int expo) 
{
    if (coef == 0) return;
    NODE* newNode = new NODE{ coef, expo, nullptr };
    if (head == nullptr) 
    {
        head = last = newNode;
    }
    else 
    {
        last->link = newNode;
        last = newNode;
    }
}

void CPolyList::Print() 
{
    NODE* curr = head;
    bool first = true;
    while (curr != nullptr) 
    {
        if (!first && curr->coef > 0) cout << "+";

        if (curr->expo == 0) 
        {
            cout << curr->coef;  // �����
        }
        else if (curr->expo == 1) 
        {
            cout << curr->coef << "x";  // 1����
        }
        else 
        {
            cout << curr->coef << "x^" << curr->expo; // 1������ ������ ������ �� ���
        }

        first = false;
        curr = curr->link;;
    }
    cout << endl;
}

void CPolyList::AddPoly(CPolyList& Q, CPolyList& R) 
{
    R.Clear(); // ��� ����Ʈ R �ʱ�ȭ
    NODE* p = this->head;
    NODE* q = Q.head;

    while (p != nullptr && q != nullptr) 
    {
        if (p->expo == q->expo) 
        {
            int sum = p->coef + q->coef;
            if (sum != 0) R.AppendTerm(sum, p->expo);
            p = p->link;
            q = q->link;
        }
        else if (p->expo < q->expo) 
        {
            R.AppendTerm(q->coef, q->expo);
            q = q->link;
        }
        else 
        {
            R.AppendTerm(p->coef, p->expo);
            p = p->link;
        }
    }

    while (p != nullptr) 
    {
        R.AppendTerm(p->coef, p->expo);
        p = p->link;
    }

    while (q != nullptr) 
    {
        R.AppendTerm(q->coef, q->expo);
        q = q->link;
    }

    R.Simplify();
}

void CPolyList::MultiPoly(CPolyList& Q, CPolyList& R) 
{
    R.Clear();  //��� ����Ʈ R �߰�
    for (NODE* p = this->head; p != nullptr; p = p->link) 
    {
        for (NODE* q = Q.head; q != nullptr; q = q->link) 
        {
            int coef = p->coef * q->coef;
            int expo = p->expo + q->expo;
            R.AppendTerm(coef, expo);
            /*NODE* r = R.head;
            NODE* prev = nullptr;
            while (r != nullptr && r->expo > expo) 
            {
                prev = r;
                r = r->link;
            }
            if (r != nullptr && r->expo == expo) 
            {
                r->coef += coef;
                if (r->coef == 0) 
                {
                    if (prev == nullptr) R.head = r->link;
                    else prev->link = r->link;
                    delete r;
                }
            }
            else 
            {
                NODE* newNode = new NODE{ coef, expo, r };
                if (prev == nullptr) 
                {
                    R.head = newNode;
                }
                else 
                {
                    prev->link = newNode;
                }
                if (newNode->link == nullptr) R.last = newNode;
            }*/ 
            // ���� ���� �ڵ�. ������, x^n �׿��� ��ȣ�� �����ǰų� �ߺϵɶ�, ����� ã�� ���� �ּ�ó��
            // Simplify() �ڵ带 Ȱ���ؼ� ���ǿ� �´� ���ο� ���� �ڵ� Ȱ��
        }
    }
    R.Simplify();
}


void CPolyList::Simplify()
{
    if (!head || !head->link) return;

    // 1. ���� (���� ���� ��������)
    bool swapped;
    do {
        swapped = false;
        NODE** curr = &head;
        while ((*curr) && (*curr)->link) {
            NODE* a = *curr;
            NODE* b = a->link;
            if (a->expo < b->expo) {
                a->link = b->link;
                b->link = a;
                *curr = b;
                swapped = true;
            }
            curr = &((*curr)->link);
        }
    } while (swapped);

    // 2. �ߺ� �� ����
    NODE* curr = head;
    while (curr && curr->link)
    {
        if (curr->expo == curr->link->expo) 
        {
            curr->coef += curr->link->coef;
            NODE* temp = curr->link;
            curr->link = temp->link;
            delete temp;
        }
        else 
        {
            curr = curr->link;
        }
    }

    // 3. ��� 0 ����
    NODE** curr_ptr = &head;
    while (*curr_ptr) 
    {
        if ((*curr_ptr)->coef == 0) 
        {
            NODE* temp = *curr_ptr;
            *curr_ptr = temp->link;
            delete temp;
        }
        else 
        {
            curr_ptr = &((*curr_ptr)->link);
        }
    }
}