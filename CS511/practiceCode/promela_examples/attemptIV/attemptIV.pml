bool wantP = false, wantQ = false; 
bool csp;
ltl p1 {<> csp}
active proctype P() {
  do
  :: wantP = true;
    do
    :: wantQ -> wantP = false; wantP = true :: else -> break
    od;
    csp = true; csp = false;
    wantP = false
  od
}
active proctype Q() {
  do
  :: wantQ = true;
    do
    :: wantP -> wantQ = false; wantQ = true :: else -> break
    od;
    wantQ = false
  od
}