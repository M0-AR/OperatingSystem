public class RaceCondition {
    public static void main(String[] args) {
        Bank bank = new Bank();
        AccountHolder accountHolder = new AccountHolder(bank);
        Thread t1 = new Thread(accountHolder);
        Thread t2 = new Thread(accountHolder);
        Thread t3 = new Thread(accountHolder);
        Thread t4 = new Thread(accountHolder);

        t1.setName("Thread-1");
        t2.setName("Thread-2");
        t2.setName("Thread-3");
        t2.setName("Thread-4");

        t1.start();
        t2.start();
        t3.start();
        t4.start();

    }
}

class Bank {
    double balance = 4500;

    public void withdraw(int amount) {
        balance -= amount;
    }
}

class AccountHolder implements Runnable {
    private Bank bank;

    public AccountHolder(Bank bank) {
        this.bank = bank;
    }

    @Override
    public void run() {
        for (int i = 1; i <= 1; i++) {
            makeWithdrawal(1500);
            if (bank.balance < 0) {
                System.out.println("account is overdrawn!: " + bank.balance);
            }
        }
    }

    private synchronized void makeWithdrawal(int withdrawAmount) {
        if (bank.balance >= withdrawAmount) {
            System.out.println(Thread.currentThread().getName()	+ " is going to withdraw $"+withdrawAmount);
            try {
                Thread.sleep( 500 );
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            bank.withdraw(withdrawAmount);
            System.out.println(Thread.currentThread().getName()	+ " completes the withdrawal of $"+withdrawAmount);
        } else {
            System.out.println("Not enough money in bank for "	+ Thread.currentThread().getName() + " to withdraw "
                    + bank.balance);
        }
    }
}