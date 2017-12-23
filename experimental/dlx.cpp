#include <iostream>
#include <vector>
#include <cstdint>

struct node_struct
{
    node_struct *C;
    node_struct *U;
    node_struct *D;
    node_struct *L;
    node_struct *R;
    int size;

    void unlink_UD() { this->U->D = this->D; this->D->U = this->U; }
    void link_UD() { this->U->D = this; this->D->U = this; }
    void unlink_LR() { this->L->R = this->R; this->R->L = this->L; }
    void link_LR() { this->L->R = this; this->R->L = this; }

    void cover()
    {
        unlink_LR();
        for (node_struct *i = this->D; i != this; i = i->D)
        {
            for (node_struct *j = i->R; j != i; j = j->R)
            {
                j->unlink_UD();
                j->C->size--;
            }
        }
    }

    void uncover()
    {
        for (node_struct *i = this->U; i != this; i = i->U)
        {
            for (node_struct *j = i->L; j != i; j = j->L)
            {
                j->C->size++;
                j->link_UD();
            }
        }
        link_LR();
    }
};

uint64_t search(node_struct *header)
{
    if (header->size == 0)
        return 1;
    
    int smallest_size = -1;
    node_struct *column = nullptr;
    for (node_struct *C = header->R; C != header; C = C->R)
    {
        if (smallest_size == -1 || C->size < smallest_size)
        {
            smallest_size = C->size;
            column = C;
        }
    }
    
    if (column->size == 0)
        return 0;
    
    uint64_t count = 0;

    column->cover();
    header->size--;

    for (node_struct *i = column->D; i != column; i = i->D)
    {
        for (node_struct *j = i->R; j != i; j = j->R)
        {
            j->C->cover();
            header->size--;
        }

        count += search(header);

        for (node_struct *j = i->L; j != i; j = j->L)
        {
            header->size++;
            j->C->uncover();
        }
    }

    header->size++;
    column->uncover();

    return count;
}

node_struct *create_table(std::vector<std::vector<bool>> const &array)
{
    node_struct *header = new node_struct();
    header->L = header;
    header->R = header;

    for (int i = 0; i < array[0].size(); i++)
    {
        node_struct *C = new node_struct();
        C->U = C;
        C->D = C;
        C->L = header->L;
        C->R = header;
        header->L->R = C;
        header->L = C;
        header->size++;
    }

    for (int i = 0; i < array.size(); i++)
    {
        node_struct *C = header;
        node_struct *row_header = nullptr;

        for (int j = 0; j < array[i].size(); j++)
        {
            C = C->R;
            if (array[i][j])
            {
                if (row_header == nullptr)
                {
                    row_header = new node_struct();
                    row_header->C = C;
                    row_header->U = C->U;
                    row_header->D = C;
                    C->U->D = row_header;
                    C->U = row_header;
                    row_header->L = row_header;
                    row_header->R = row_header;
                    C->size++;
                }
                else
                {
                    node_struct *node = new node_struct();
                    node->C = C;
                    node->U = C->U;
                    node->D = C;
                    C->U->D = node;
                    C->U = node;
                    node->L = row_header->L;
                    node->R = row_header;
                    row_header->L->R = node;
                    row_header->L = node;
                    C->size++;
                }
            }
        }
    }

    return header;
}