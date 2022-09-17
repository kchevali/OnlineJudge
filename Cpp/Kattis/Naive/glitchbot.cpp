#include <bits/stdc++.h>
using namespace std;
typedef long long l;

class Vector {
    public:
    l x = 0, y = 0;

    Vector() {}
    Vector(l x, l y){
        this->x = x;
        this->y = y;
    }

    void left(){
        l tdx = -this->y, tdy = this->x;
        this->x = tdx, this->y = tdy;
    }

    void right(){
        l tdx = this->y, tdy = -this->x;
        this->x = tdx, this->y = tdy;
    }

    void sum(Vector& other){
        this->x += other.x, this->y += other.y;
    }

    Vector copy() {
        return Vector(this->x, this->y);
    }

    static bool equals(Vector& a, Vector& b){
        return a.x == b.x && a.y == b.y;
    }

    static Vector sub(Vector& a, Vector& b){
        return Vector(a.x - b.x, a.y - b.y);
    }
};

class Robot {
    public:
    Vector position, direction;

    Robot(): position(0, 0), direction(0, 1) {}
    Robot(l x, l y, l dx, l dy): position(x, y), direction(dx, dy) {}

    void move(l step){
        if(step == 0) this->position.sum(this->direction);
        else if(step < 0) this->direction.left();
        else this->direction.right();
    }

    Robot copy(){
        return Robot(this->position.x, this->position.y, this->direction.x, this->direction.y);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Vector target;

    l n;
    cin >> target.x >> target.y >> n;

    l steps[n];
    string s;

    Robot end;
    for(l i = 0; i < n; i++){
        cin >> s;
        steps[i] = s[0] == 'F' ? 0 : (s[0] == 'L' ? -1 : 1);
        end.move(steps[i]);
    }

    Robot x;
    for(l i = 0; i < n; i++){
        Robot prevX = x.copy();
        x.move(steps[i]);

        Vector diff = Vector::sub(end.position, x.position);
        for(l j = -1; j <= 1; j++){
            if(j == steps[i]) continue;

            Robot newX = prevX.copy();
            newX.move(j);
            
            Vector newDiff = diff.copy();
            while(!Vector::equals(newX.direction, x.direction)){
                newX.direction.left();
                newDiff.right();
            }

            newX.position.sum(newDiff);
            if(Vector::equals(target, newX.position)){
                cout << (i+1) << " " << (j == -1 ? "Left" : (j == 0 ? "Forward" : "Right")) << "\n";
                return 0;
            }
        }
    }

}
