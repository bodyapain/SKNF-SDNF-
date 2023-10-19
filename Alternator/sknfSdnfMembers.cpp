#include "sknfSdnfMembers.h"

//������� ������ ����
void sknfSearch(bool wantedValue, list<sknfMember>& lst, node* node) {

    if (lst.size() == 0) {   //���� �������� ������� ������ ������ (�� ������������, � ������ ����������!) - �������� ���� ��� ������ ������. �������
        return;
    }

    if (node->value < 0) {         //���� ������ � ��������

        if (node->value == -1) {   //� ������ ��������� ����������� �������� �������� � ��������� ����� �������
            sknfSearch(!wantedValue, lst, node->right);
            return;
        }
        if (operands[abs(node->value) - 2][wantedValue][0] == 1) {   // ���� ���� ��������� ����

            if (node->rightWeight < node->leftWeight) {         //���� �� ������� ����� ����� ������� ������ � ����������, ��� ������ �������, ����� ������
                sknfSearch(operands[abs(node->value) - 2][wantedValue][2], lst, node->right);
                sknfSearch(operands[abs(node->value) - 2][wantedValue][1], lst, node->left);
            }
            else {             //� ��������� ������ ��� ������, ����� �������
                sknfSearch(operands[abs(node->value) - 2][wantedValue][1], lst, node->left);
                sknfSearch(operands[abs(node->value) - 2][wantedValue][2], lst, node->right);
            }
            return;
        }
        if (operands[abs(node->value) - 2][wantedValue][0] == 2) {   //���� ��� ��������� ���

            globalStack.push(lst);   //���������� �� �������� ����� ��������� ��� ������������ ������� ������. ������� �� �� ����

            if (node->rightWeight < node->leftWeight) {            //��������, ����������� ������� ������

                sknfSearch(operands[abs(node->value) - 2][wantedValue][2], lst, node->right); //����� ����� � ������ �� ������� ��������
                sknfSearch(operands[abs(node->value) - 2][wantedValue][1], lst, node->left);

                sknfSearch(operands[abs(node->value) - 2][wantedValue][4], globalStack.top(), node->right);  //����� ������� � ������ �� �������, ���������� � �����
                sknfSearch(operands[abs(node->value) - 2][wantedValue][3], globalStack.top(), node->left);
            }
            else {
                sknfSearch(operands[abs(node->value) - 2][wantedValue][1], lst, node->left);
                sknfSearch(operands[abs(node->value) - 2][wantedValue][2], lst, node->right);

                sknfSearch(operands[abs(node->value) - 2][wantedValue][3], globalStack.top(), node->left);
                sknfSearch(operands[abs(node->value) - 2][wantedValue][4], globalStack.top(), node->right);
            }
            lst.insert(lst.end(), globalStack.top().begin(), globalStack.top().end());   //��������� ���������� ����� ������� � ������ ��������
            globalStack.pop();   //������ ��������� ������� ������ �� �����
            return;
        }
        if (operands[abs(node->value) - 2][wantedValue][0] == 3) {  //���� ��� ��������� 3

            globalStack.push(lst);  //���������� �� �������� ����� ��������� ��� ������������ ������� � �������� ������. ������� �� �� ����

            /*� ������ ��� ��� ���� ����������� ��������� ������. ����� ��� ��� ���� ����� ����������� 2 ���� � ����� ����� ��������, � ����� ������
            * ��������, ���������� ��� 1 �� ����� (0,0), (0,1). (1,1). ���� �������� ����� �����, �� ������ 0 ����� ����� ������ 1 ���, � ����
            * �������� ������ ������, �� ������� ������ 1 ���. ����� ������� ���������� 3 ���� �� 5 ������� ������ 6.
            */
            if (node->rightWeight < node->leftWeight) {     //���������� ������ 1

                sknfSearch(operands[abs(node->value) - 2][wantedValue][4], lst, node->right);  //���������� "������������" ������. ���, ��� �������� � ������ � ������� ����� ���� ��������
                sknfSearch(operands[abs(node->value) - 2][wantedValue][3], lst, node->left);

                sknfSearch(operands[abs(node->value) - 2][wantedValue][2], globalStack.top(), node->right);  //������ ������� ����� ��� ���� ���������� ������� ��� ������ ������ �� �����

                globalStack.push(globalStack.top()); //��������� � ���� ��������� "������" ������, ����� ��������� 2 ��������� ������

                sknfSearch(operands[abs(node->value) - 2][wantedValue][1], globalStack.top(), node->left);    //��� ������ �� ������ �� �����
                lst.insert(lst.end(), globalStack.top().begin(), globalStack.top().end());  //������� ��������� � ������ ��������

                globalStack.pop();   //������ �� ����� ���� ������

                sknfSearch(operands[abs(node->value) - 2][wantedValue][5], globalStack.top(), node->left); //������ ������ ��� �������� ������
            }
            else {
                sknfSearch(operands[abs(node->value) - 2][wantedValue][1], lst, node->left);
                sknfSearch(operands[abs(node->value) - 2][wantedValue][2], lst, node->right);

                sknfSearch(operands[abs(node->value) - 2][wantedValue][3], globalStack.top(), node->left);

                globalStack.push(globalStack.top());

                sknfSearch(operands[abs(node->value) - 2][wantedValue][4], globalStack.top(), node->right);
                lst.insert(lst.end(), globalStack.top().begin(), globalStack.top().end());

                globalStack.pop();

                sknfSearch(operands[abs(node->value) - 2][wantedValue][6], globalStack.top(), node->right);
            }
            lst.insert(lst.end(), globalStack.top().begin(), globalStack.top().end());  //������� � ����� ������ �������� ��������� ���������� �������� ������
            globalStack.pop();  //������ �� ����� ������ �������� ������
            return;
        }
    }
    else {    //���� ����� ���� ����������

        //���� ������ ������ ����������, ������ ������� ���� ���� ���������� �� ����� ����������
        //����� �������� ������ ������ �� ����, �� �������� ������� ��� ����������, � �� �������� ����������� �������� - "�����"
        //� ��� ����� ������ ���������� �������� 1, ��� �������� ���������. �� � ����� ���������� � ������ ���������� ��������� 0
        //������ ��� �������� ��������� if
        if (lst.size() == 1 && (*lst.begin()).signs.test(0) && !((*lst.begin()).vars.test(0))) {

            (*lst.begin()).signs.set(0, 0);   //����� "�����"
            (*lst.begin()).vars.set(node->value - 1, 1);  //������� ��������� ����������
            (*lst.begin()).signs.set(node->value - 1, wantedValue);   //� ������� �� ����
            return;
        }
        else {  //���� �� ������ ���������� �� ����, ���� ������ �� ���� � �������� ���������� ����, ��� �� �� �������. ��� ������������� �������� ����������

            it1 = lst.begin();  //������� �������� �������� � ������ ������ ����������

            while (it1 != lst.end()) {

                if ((*it1).vars.test(node->value - 1)) {
                    if ((*it1).signs.test(node->value - 1) != wantedValue) {
                        lst.erase(it1++);
                    }
                    else {
                        ++it1;
                    }
                }
                else {
                    (*it1).vars.set(node->value - 1, 1);
                    (*it1).signs.set(node->value - 1, wantedValue);
                    ++it1;
                }
            }
            return;
        }
    }
}

//������� ������ ����
void sdnfSearch(bool wantedValue, list<sknfMember>& lst, node* node) {

    if (lst.size() == 0) {   //���� �������� ������� ������ ������ (�� ������������, � ������ ����������!) - �������� ���� ��� ������ ������. �������
        return;
    }

    if (node->value < 0) {         //���� ������ � ��������

        if (node->value == -1) {   //� ������ ��������� ����������� �������� �������� � ��������� ����� �������
            sdnfSearch(!wantedValue, lst, node->right);
            return;
        }
        if (operands[abs(node->value) - 2][wantedValue][0] == 1) {   // ���� ���� ��������� ����

            if (node->rightWeight < node->leftWeight) {         //���� �� ������� ����� ����� ������� ������ � ����������, ��� ������ �������, ����� ������
                sdnfSearch(operands[abs(node->value) - 2][wantedValue][2], lst, node->right);
                sdnfSearch(operands[abs(node->value) - 2][wantedValue][1], lst, node->left);
            }
            else {             //� ��������� ������ ��� ������, ����� �������
                sdnfSearch(operands[abs(node->value) - 2][wantedValue][1], lst, node->left);
                sdnfSearch(operands[abs(node->value) - 2][wantedValue][2], lst, node->right);
            }
            return;
        }
        if (operands[abs(node->value) - 2][wantedValue][0] == 2) {   //���� ��� ��������� ���

            globalStack.push(lst);   //���������� �� �������� ����� ��������� ��� ������������ ������� ������. ������� �� �� ����

            if (node->rightWeight < node->leftWeight) {            //��������, ����������� ������� ������

                sdnfSearch(operands[abs(node->value) - 2][wantedValue][2], lst, node->right); //����� ����� � ������ �� ������� ��������
                sdnfSearch(operands[abs(node->value) - 2][wantedValue][1], lst, node->left);

                sdnfSearch(operands[abs(node->value) - 2][wantedValue][4], globalStack.top(), node->right);  //����� ������� � ������ �� �������, ���������� � �����
                sdnfSearch(operands[abs(node->value) - 2][wantedValue][3], globalStack.top(), node->left);
            }
            else {
                sdnfSearch(operands[abs(node->value) - 2][wantedValue][1], lst, node->left);
                sdnfSearch(operands[abs(node->value) - 2][wantedValue][2], lst, node->right);

                sdnfSearch(operands[abs(node->value) - 2][wantedValue][3], globalStack.top(), node->left);
                sdnfSearch(operands[abs(node->value) - 2][wantedValue][4], globalStack.top(), node->right);
            }
            lst.insert(lst.end(), globalStack.top().begin(), globalStack.top().end());   //��������� ���������� ����� ������� � ������ ��������
            globalStack.pop();   //������ ��������� ������� ������ �� �����
            return;
        }
        if (operands[abs(node->value) - 2][wantedValue][0] == 3) {  //���� ��� ��������� 3

            globalStack.push(lst);  //���������� �� �������� ����� ��������� ��� ������������ ������� � �������� ������. ������� �� �� ����

            /*� ������ ��� ��� ���� ����������� ��������� ������. ����� ��� ��� ���� ����� ����������� 2 ���� � ����� ����� ��������, � ����� ������
            * ��������, ���������� ��� 1 �� ����� (0,0), (0,1). (1,1). ���� �������� ����� �����, �� ������ 0 ����� ����� ������ 1 ���, � ����
            * �������� ������ ������, �� ������� ������ 1 ���. ����� ������� ���������� 3 ���� �� 5 ������� ������ 6.
            */
            if (node->rightWeight < node->leftWeight) {     //���������� ������ 1

                sdnfSearch(operands[abs(node->value) - 2][wantedValue][4], lst, node->right);  //���������� "������������" ������. ���, ��� �������� � ������ � ������� ����� ���� ��������
                sdnfSearch(operands[abs(node->value) - 2][wantedValue][3], lst, node->left);

                sdnfSearch(operands[abs(node->value) - 2][wantedValue][2], globalStack.top(), node->right);  //������ ������� ����� ��� ���� ���������� ������� ��� ������ ������ �� �����

                globalStack.push(globalStack.top()); //��������� � ���� ��������� "������" ������, ����� ��������� 2 ��������� ������

                sdnfSearch(operands[abs(node->value) - 2][wantedValue][1], globalStack.top(), node->left);    //��� ������ �� ������ �� �����
                lst.insert(lst.end(), globalStack.top().begin(), globalStack.top().end());  //������� ��������� � ������ ��������

                globalStack.pop();   //������ �� ����� ���� ������

                sdnfSearch(operands[abs(node->value) - 2][wantedValue][5], globalStack.top(), node->left); //������ ������ ��� �������� ������
            }
            else {
                sdnfSearch(operands[abs(node->value) - 2][wantedValue][1], lst, node->left);
                sdnfSearch(operands[abs(node->value) - 2][wantedValue][2], lst, node->right);

                sdnfSearch(operands[abs(node->value) - 2][wantedValue][3], globalStack.top(), node->left);

                globalStack.push(globalStack.top());

                sdnfSearch(operands[abs(node->value) - 2][wantedValue][4], globalStack.top(), node->right);
                lst.insert(lst.end(), globalStack.top().begin(), globalStack.top().end());

                globalStack.pop();

                sdnfSearch(operands[abs(node->value) - 2][wantedValue][6], globalStack.top(), node->right);
            }
            lst.insert(lst.end(), globalStack.top().begin(), globalStack.top().end());  //������� � ����� ������ �������� ��������� ���������� �������� ������
            globalStack.pop();  //������ �� ����� ������ �������� ������
            return;
        }
    }
    else {    //���� ����� ���� ����������

        //���� ������ ������ ����������, ������ ������� ���� ���� ���������� �� ����� ����������
        //����� �������� ������ ������ �� ����, �� �������� ������� ��� ����������, � �� �������� ����������� �������� - "�����"
        //� ��� ����� ������ ���������� �������� 1, ��� �������� ���������. �� � ����� ���������� � ������ ���������� ��������� 0
        //������ ��� �������� ��������� if
        if (lst.size() == 1 && (*lst.begin()).signs.test(0) && !((*lst.begin()).vars.test(0))) {

            (*lst.begin()).signs.set(0, 0);   //����� "�����"
            (*lst.begin()).vars.set(node->value - 1, 1);  //������� ��������� ����������
            (*lst.begin()).signs.set(node->value - 1, !wantedValue);   //� ������� �� ����
            return;
        }
        else {  //���� �� ������ ���������� �� ����, ���� ������ �� ���� � �������� ���������� ����, ��� �� �� �������. ��� ������������� �������� ����������

            it1 = lst.begin();  //������� �������� �������� � ������ ������ ����������

            while (it1 != lst.end()) {

                if ((*it1).vars.test(node->value - 1)) {
                    if ((*it1).signs.test(node->value - 1) != !wantedValue) {
                        lst.erase(it1++);
                    }
                    else {
                        ++it1;
                    }
                }
                else {
                    (*it1).vars.set(node->value - 1, 1);
                    (*it1).signs.set(node->value - 1, !wantedValue);
                    ++it1;
                }
            }
            return;
        }
    }
}

