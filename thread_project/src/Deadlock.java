class Deadlock {
    public static void main(String [] args) throws InterruptedException {
        final Account account1 = new Account(1,1000);
        final Account account2 = new Account(2,300);
        Thread a = new Thread( () -> transfer(account1,account2,200, "Thread_01") );
        Thread b = new Thread( () -> transfer(account2,account1,300, "Thread_02") );
        a.start();
        b.start();

        Thread.sleep( 2000 ); // Sleep a bit while threads are working then show the result
        System.out.println(account1.balance);
        System.out.println(account2.balance);
    }

    public static void transfer(Account fromObject1, Account toObject2, double amount, String name)  {
        Account first = fromObject1;
        Account second = toObject2;
        if (first.compareTo(second) < 0) {
            // Swap them
            first = toObject2;
            second = fromObject1;
        }
        synchronized(first) { // Grab a lock for first object
            fromObject1.withdraw(amount);
            System.out.println("NoDeadLock-> first synchronized: " + name + " acquired " + fromObject1);
            try {
                Thread.sleep( 500 ); // Sleep a bit before acquire the second lock
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            synchronized(second) { // Grab a lock for second object
                toObject2.deposit(amount);
                System.out.println("NoDeadLock-> second synchronized: " + name + " acquired " + fromObject1);
            }
        }
    }
}