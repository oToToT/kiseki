lld modu(lld a, lld m){
    while(a >= m) a -= m;
    return a;
}
lld mul(lld a, lld b, lld m){
    if(a < b) swap(a, b);
    lld ret = 0;
    while(b){
        if(b & 1) ret = modu(ret+a, m);
        a = modu(a+a, m);
        b >>= 1;
    }
    return ret;
}
lld qPow(lld a, lld k, lld m){
    lld ret = 1;
    a %= m;
    while(k){
        if(k & 1) ret = mul(ret, a, m);
        a = mul(a, a, m);
        k >>= 1;
    }
    return modu(ret, m);
}
bool witness(lld a, lld s, int t, lld n){
    lld b = qPow(a, s, n);
    if(b == 0) return false;
    while(t--){
        lld bb = mul(b, b, n);
        if(bb == 1 and b != 1 and b != n-1) return true;
        b = bb;
    }
    return b != 1;
}
bool miller_rabin(lld n){
    if(n < 2) return false;
    if(!(n & 1)) return (n==2);
    lld x = n-1; int t = 0;
    while(!(x&1)) x >>= 1, t++;
    lld sprp[] = {2,325,9375,28178,450775,9780504,1795265022};
    for(int i=0;i<7;i++){
        if(witness(sprp[i]%n, x, t, n)) return false;
    }
    return true;
}
