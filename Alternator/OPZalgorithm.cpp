#include "OPZalgorithm.h"
//------------------��������_��_���-----------------// 

//Reverse Polish Notation - �������� �������� ������
//������ ��� �������� �������� �������� ������ (���) ���������, ��� ������� �� ������
vector<short> rpn;
extern int numOfVars;   //������ ���������� ���������� � �������, ����� ��� ����������� ������� ����� ������� ����� ������������ ���
//��������� �������� ����� ������, ������� ���
void postOrderTravers(node* node) {
    if (node == nullptr)
        return;
    postOrderTravers(node->left);
    postOrderTravers(node->right);
    rpn.push_back(node->value);
}

//���������� ������� � ������� ����� (��� � �������� �����)
void incBitSet(bitset<NEW_ALGO_MAX_VARS>& bitset) {
    for (int i = 0; i < NEW_ALGO_MAX_VARS; i++) {
        if (!bitset.test(i)) {
            bitset.set(i, 1);
            for (int j = 0; j < i; j++) {
                bitset.set(j, 0);
            }
            break;
        }
    }
}

//������� ������ ���� (����)
vector<bitset<NEW_ALGO_MAX_VARS>> rpnCalcutator(node* node, int flag) {
    bool toFind = 0;
    if (flag == FLAG_SDNF) {
        toFind = 1;
    }
    else if (flag == FLAG_SKNF) {
        toFind = 0;
    }


    int bitToCheck = numOfVars;   //��� ��� ������� ����� ����������� (����� ���������� ������), ��������� ������������ ����� ������� ����� ����� ����������� ����������
    vector <bitset<NEW_ALGO_MAX_VARS>> ans; //���� �������� �����

    bitset<NEW_ALGO_MAX_VARS> curSet(0);       //����� ������� ����������

    bitset<NEW_ALGO_STACK_LIMIT> stack(0);     //�����, ����������� ���� �����
    int topIndex;  //������ ������� ������� �������� � �����

    postOrderTravers(node); //����� �������� �������� ������

    while (!curSet.test(bitToCheck)) {  // ���� �� ����� n ����������, ������������ ���� ����� � �������� 0 - (n-1). ����� ��� � ������� n ������ ������ 1, ��� ������ �� ������������ ��� ����� ���� �����������
        topIndex = 0;   //"�������" ����. �� ����� ���� ���������� � ������ ������ �������� ��������� �� ������� �������� �������� �����, ����� ������ �������������� ��.

        for (int i = 0; i < rpn.size(); i++) {   //���� �� �������� �������� ������ �������

            if (rpn[i] > 0) {  //���� ������ � ����������

                stack.set(topIndex, curSet.test(rpn[i] - 1));   //�������� �� ���� � �������� � ������� ��������������� ������
                topIndex += 1;  //������� ������ �������� ����� (���� �������� ���� �������)
            }
            else {                 //� ��������� ������ ����� ���� ��������
                switch (rpn[i]) {
                case -1:   //���������
                {
                    //stack.set(topIndex - 1, !stack.test(topIndex - 1));
                    stack.flip(topIndex - 1);    //����������� ��������� ������� �����
                }; break;

                case -2:  // ����������
                {
                    stack.set(topIndex - 2, stack.test(topIndex - 2) && stack.test(topIndex - 1));
                    topIndex -= 1;
                }; break;

                case -3: // ����������
                {
                    stack.set(topIndex - 2, stack.test(topIndex - 2) || stack.test(topIndex - 1));
                    topIndex -= 1;
                }; break;

                case -4: // XOR (����������� ���)
                {
                    stack.set(topIndex - 2, stack.test(topIndex - 2) ^ stack.test(topIndex - 1));
                    topIndex -= 1;
                }; break;

                case -5: // ����������
                {
                    stack.set(topIndex - 2, !stack.test(topIndex - 2) || stack.test(topIndex - 1));
                    topIndex -= 1;
                }; break;

                case -6: //������������
                {
                    stack.set(topIndex - 2, stack.test(topIndex - 2) == stack.test(topIndex - 1));
                    topIndex -= 1;
                }; break;

                case -7: //����� ������� (��-�)
                {
                    stack.set(topIndex - 2, !(stack.test(topIndex - 2) && stack.test(topIndex - 1)));
                    topIndex -= 1;
                }; break;

                case -8: //������� ����� (��-���)
                {
                    stack.set(topIndex - 2, !(stack.test(topIndex - 2) || stack.test(topIndex - 1)));
                    topIndex -= 1;
                }; break;
                }
            }
        }

        if (stack.test(0) == toFind) {   //���� ������� �� ������ ������ ���� 0 (1) - �������� ����� � ���� (����)
            ans.push_back(curSet);
        }
        incBitSet(curSet);
    }

    return ans;
}