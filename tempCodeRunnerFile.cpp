Node* searchbyName(Node *pHead)
{
    cout<<"Nhap ten quoc gia: ";
    string name;
    getline(cin,name);
    string outstr;
    outstr = process(name);
    cout<<name;
    while (!strcmp(pHead -> info.strName,name)  && pHead) {
        pHead = pHead -> nextName;
    }
    return pHead;
}