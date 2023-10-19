#pragma once
#include "main.h"
#include "tree.h"

//��������� - ���� ����(����)
//������������ ����� �������� �������
//���� i-� ��� � ������ ����� ���������� � 1, ������ ���������� ��� ������� � ����������
//������ ����� ������ ���������� � ����� ���������� � ���� �� i-�� �����. (0 - ��� ���������, 1- ���� ���������)
struct sknfMember {
    bitset <MAX_VARS> vars;    //����� ����������
    bitset <MAX_VARS> signs;   //����� ������ ����������
};

//���������� ����������, ������� ���������� ������� ������
//��������� ���������, �.�. ��������� ���� �� ������ ���������� ������ � ����� ������ �������
//----------------------------------------------------------------------
void sknfSearch(bool wantedValue, list<sknfMember>& lst, node* node);
void sdnfSearch(bool wantedValue, list<sknfMember>& lst, node* node);
extern list<sknfMember>::iterator it1;        //�������� ��� ����������� �� ������ ����������
extern stack <list<sknfMember>> globalStack;   //���������� ���� ��� ���������� ������, ��������� �� ��������
list<list<short>> listOfBitsetsToListOfShorts(list<sknfMember> lst);
