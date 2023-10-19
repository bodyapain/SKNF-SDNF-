#pragma once
#include "main.h"
#include "expressionFunctions.h"
//���������, ������������ ���� ������ ���������
struct node
{

    struct node* left = nullptr;   //��������� �� ������ �������
    struct node* right = nullptr;  //��������� �� ������� �������
    short value = 0;               //�������� ���� - ����� ���������� (������������� �����) ��� ����� ��������� (������������� �����)
    short leftWeight = 0;          //��� ������ �����
    short rightWeight = 0;         //��� ������� �����
};
int distToLeaf(node* node);
void addnode(string expression, node* tree);