
#include "tree.h"
extern int numOfVars;
//������� ���������� �� ������� �� ���������� �����-����������
int distToLeaf(node* node) {

    if (node->value > 0)   //���� ������ � ���������� - �������. ���������� ����� ��� ������ � ������� ����� ������ 0.
        return 0;

    if (node->value == -1) {        //���� ������ � ���������
        node->leftWeight = 999; // ��������� ����� ��������� ���������. ���� �� ��������� ������� �� �����������
        node->rightWeight = distToLeaf(node->right) + 1;    //����� ��� ������� ����� � �������� � ���� 1 (���� ������ ����������, �� ���������� �� �� - 1)
        return node->rightWeight;
    }
    node->leftWeight = distToLeaf(node->left) + 1;          //� ������ ������ ���������� ������� ��� ������ � ������� ����� � ���������� ���������� �� ���
    node->rightWeight = distToLeaf(node->right) + 1;
    return min(node->leftWeight, node->rightWeight);

}
//��������� ���� � ������ ���������
void addnode(string expression, node* tree) {

    removeOuterBraces(expression);   //������ ������� ������ (�+b) -> a+b

    int lpIndex = find_low_priority_operator(expression); //����� ������ �������� ������������� ���������

    //���� ��������� ���, �� ����� ������, ���������� ������ ���� ����������, ����. a15. ������� �� ����� � ���� �����
    if (lpIndex == -1) {
        stringstream intVarContainer(expression.substr(1, expression.size() - 1));
        int intVar;
        intVarContainer >> intVar;
        tree->value = intVar;
        if (numOfVars < intVar) numOfVars = intVar;
        return;
    }
    tree->value = getOperatorsIntForm(expression[lpIndex]);   //� ��������� ������ ����� �������� - ������� ��� ����� � ���� ������

    if (tree->value == -1) {        //���� ������ � ���������, ���������� ������� ������ ������ ���������. ��������� - ������� ��������
        tree->right = new node;
        addnode(expression.substr(lpIndex + 1), tree->right);
    }
    else {                                          //� ��������� ������ ������ ��� ���������
        tree->left = new node;
        tree->right = new node;
        addnode(expression.substr(0, lpIndex), tree->left);
        addnode(expression.substr(lpIndex + 1), tree->right);
    }
}
