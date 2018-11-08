// ax+ny = 1, ax+ny == ax == 1 (mod n)
pair<lld,lld> exgcd(lld a, lld b){
    if(b == 0) return {1, 0};
    pair<lld,lld> q = gcd(b, a % b);
    return {q.second, q.first - q.second * (a / b)};
}

lld crt(lld ans[], lld pri[], int n){
    lld M = 1;
    for(int i=0;i<n;i++) M *= pri[i];
    lld ret = 0;
    for(int i=0;i<n;i++){
        lld inv = (gcd(M/pri[i], pri[i]).first + pri[i])%pri[i];
        ret += (ans[i]*(M/pri[i])%M * inv)%M;
        ret %= M;
    }
    return ret;
}
/*
Another:
x = a1 % m1
x = a2 % m2
g = gcd(m1, m2)
assert((a1-a2)%g==0)
[p, q] = exgcd(m2/g, m1/g)
return a2+m2*(p*(a1-a2)/g)
0 <= x < lcm(m1, m2)
*/
