#include <iostream>
#include <string>
using namespace std;

struct FileNode {
    string fileName;
    long long fileSize;       
    int h, m, s;
    FileNode* next;
    FileNode(const string& name, long long size, int hours, int minutes, int seconds) 
        : fileName(name), fileSize(size), h(hours), m(minutes), s(seconds), next(0) {}
};


struct Folder {
    FileNode* head = 0; 
};

void insertFile(Folder& folder, const string& name, long long size, int h, int m, int s) {
    FileNode* newFile = new FileNode(name,size,h,m,s);
    if (folder.head == 0) {
        folder.head = newFile; 
        return;
    }

    FileNode* current = folder.head;
    while (current->next != 0) {
        current = current->next;
    }
    current->next = newFile;
}

void sort(Folder& folder) {
    if (!folder.head || !folder.head->next) return; 

    int kt;
    do {
        kt = 0;
        FileNode* current = folder.head;
        FileNode* p = 0;

        while (current && current->next) {
            if (current->fileSize > current->next->fileSize) {
                FileNode* t = current->next;
                current->next = t->next;
                t->next = current;

                if (p) {
                    p->next = t;
                } else {
                    folder.head = t; 
                }

                kt = 1;
                p = t; 
            } else {
                p = current;
                current = current->next;
            }
        }
    } while (kt==0);
}

void printFiles(const Folder& folder) {
    FileNode* current = folder.head;
    while (current != 0) {
        cout << "File: " << current->fileName
             << ", Size: " << current->fileSize
             << " bytes, Created Time: " << current->h << ":" << current->m << ":" << current->s << endl;
        current = current->next;
    }
}

void freeList(FileNode* head) {
    while (head) {
        FileNode* t = head;
        head = head->next;
        delete t;
    }
}

void nhap(Folder& folder) {
    string c;
    do {
        string name;
        long long size;
        int h, m, s;

        cout << "File name: ";
        cin.ignore();
        getline(cin, name);
        cout << "File size: ";
        cin >> size;
        cout << "Creation time (h m s): ";
        cin >> h >> m >> s;

        insertFile(folder, name + ".txt", size, h, m, s);

        cout << "Tiep tuc (y/n): ";
        cin >> c;
    } while (c == "y");
}

void del(Folder& folder) {
    if (!folder.head) {
        cout << "Danh sách r?ng, không có file ð? xóa.\n";
        return;
    }

    FileNode* maxFile = folder.head;
    FileNode* p = 0;
    FileNode* current = folder.head;
    while (current->next) {
        p = current;
        current = current->next;
    }
    maxFile = current;

    FileNode* t = 0;
    current = folder.head;
    while (current && current->fileSize == maxFile->fileSize) {
        if (!t ||
            (current->h > t->h) || 
            (current->h == t->h && current->m > t->m) || 
            (current->h == t->h && current->m == t->m && current->s > t->s)) {
            t = current;
        }
        p = current;
        current = current->next;
    }

    if (t == folder.head) {
        folder.head = folder.head->next; 
    } else {
        current = folder.head;
        FileNode* pt = 0;

        while (current && current != t) {
            pt = current;
            current = current->next;
        }

        if (pt) {
            pt->next = t->next; 
        }
    }

    delete t;
}


int main() {
    string c = "y";
    while (c == "y") {
        Folder folder; 
        nhap(folder);

        cout << "Danh sach file trong folder:\n";
        printFiles(folder);

        sort(folder);
        cout << "Danh sach file sau khi xoa:\n";
        printFiles(folder);

		del(folder);
		cout << "Danh sach file sau khi xoa: ";
		printFiles(folder);

        freeList(folder.head);
        folder.head = 0;
		
        cout << "Them file (y/n): ";
        cin >> c;
    }

    return 0;
}

