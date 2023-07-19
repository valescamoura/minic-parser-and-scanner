int main(int i) {
    float a, b, c;
    float delta, x1, x2;

    a = 1.0;
    b = 1.0;
    c = 1.0;
    
    delta = b * b - 4 * a * c;

    if (delta > 0) {
        x1 = (-b + delta) / (2 * a);
        x2 = (-b - delta) / (2 * a);
    } 
    
    if (delta == 0) {
        x1 = -b / (2 * a);
    }

    return 0;
}