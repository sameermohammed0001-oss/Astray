let n = 10;
let a = 0;
let b = 1;

print(a);
print(b);

while (n > 2) {
    let c = a + b;
    print(c);
    a = b;
    b = c;
    n = n - 1;
}
