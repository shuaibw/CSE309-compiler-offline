int p,q,r[5];
int foo(int a, int b){
	p=9;
	int z;
	z=2*a+3*b;
	return z;
}
int main(){
	int x,y;
	x=2;
	y=5;
	int val;
	val = foo(x,y);
	printf(val);
	printf(x);
	printf(y);
	return 0;
}
