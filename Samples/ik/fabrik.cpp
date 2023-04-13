#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Joint {
public:
    double x, y, z;
    double rx, ry, rz;

    Joint(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    void setRotation(double _rx, double _ry, double _rz) {
        rx = _rx;
        ry = _ry;
        rz = _rz;
    }
};

class Link {
public:
    double length;
    Joint* start;
    Joint* end;

    Link(double _length, Joint* _start, Joint* _end) : length(_length), start(_start), end(_end) {}
};

class FABRIK {
public:
    vector<Link*> links;

    void addLink(Link* link) {
        links.push_back(link);
    }

    void solve(Joint* target) {
        // Forward reaching
        for (int i = 0; i < links.size(); i++) {
            Link* link = links[i];
            double scale = link->length / distance(link->start, link->end);
            link->end->x = link->start->x + scale * (target->x - link->start->x);
            link->end->y = link->start->y + scale * (target->y - link->start->y);
            link->end->z = link->start->z + scale * (target->z - link->start->z);
        }

        // Backward reaching
        for (int i = links.size() - 1; i >= 0; i--) {
            Link* link = links[i];
            double scale = link->length / distance(link->start, link->end);
            link->start->x = link->end->x - scale * (target->x - link->start->x);
            link->start->y = link->end->y - scale * (target->y - link->start->y);
            link->start->z = link->end->z - scale * (target->z - link->start->z);
        }
    }

private:
    double distance(Joint* j1, Joint* j2) {
        double dx = j1->x - j2->x;
        double dy = j1->y - j2->y;
        double dz = j1->z - j2->z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }
};

int main() {
    Joint* j1 = new Joint(0, 0, 0);
    Joint* j2 = new Joint(0, 0, 1);
    Joint* j3 = new Joint(0, 0, 2);
    Joint* j4 = new Joint(0, 0, 3);
    Joint* j5 = new Joint(0, 0, 4);

    Link* l1 = new Link(1, j1, j2);
    Link* l2 = new Link(1, j2, j3);
    Link* l3 = new Link(1, j3, j4);
    Link* l4 = new Link(1, j4, j5);

    FABRIK fabrik;
    fabrik.addLink(l1);
    fabrik.addLink(l2);
    fabrik.addLink(l3);
    fabrik.addLink(l4);

    Joint* target = new Joint(1, 1, 4);
    for (int i = 0; i < 10; i++) {
    fabrik.solve(target);}


    cout << "Joint 1: (" << j1->x << ", " << j1->y << ", " << j1->z << ")" << endl;
    cout << "Joint 2: (" << j2->x << ", " << j2->y << ", " << j2->z << ")" << endl;
    cout << "Joint 3: (" << j3->x << ", " << j3->y << ", " << j3->z << ")" << endl;
    cout << "Joint 4: (" << j4->x << ", " << j4->y << ", " << j4->z << ")" << endl;
    cout << "Joint 5: (" << j5->x << ", " << j5->y << ", " << j5->z << ")" << endl;

return 0;
}
