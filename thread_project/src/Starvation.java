public class Starvation {
    public static void main(String[] args) throws InterruptedException {
        final Account account1 = new Account(1,1000);
        final Account account2 = new Account(2,300);

        Thread balanceMonitorThread1 = new Thread(new BalanceMonitor(account1), "BalanceMonitor");

        Thread a = new Thread( () -> Deadlock.transfer(account1,account2,200, "Thread_01") );
        Thread b = new Thread( () -> Deadlock.transfer(account2,account1,300, "Thread_02") );

        balanceMonitorThread1.setPriority(Thread.MAX_PRIORITY);

        a.setPriority(Thread.MIN_PRIORITY);
        b.setPriority(Thread.MIN_PRIORITY);

        // Transaction threads tries to execute.
        a.start();
        b.start();

        // Start the monitor
        balanceMonitorThread1.start();


        Thread.sleep( 2000 ); // Sleep a bit while threads are working then show the result
        System.out.println(account1.balance);
        System.out.println(account2.balance);
    }
}



