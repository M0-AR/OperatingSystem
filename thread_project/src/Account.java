class Account implements Comparable<Account>{
    double balance;
    int order;

    public Account(){}

    public Account(double balance) {
        this.balance = balance;
    }

    public Account(int order, double balance){
        this.balance = balance;
        this.order = order;
    }
    void withdraw(double amount){
        balance -= amount;
    }
    void deposit(double amount){
        balance += amount;
    }


    @Override
    public int compareTo(Account o) {
        return Integer.compare( this.order, o.order );
    }

}
