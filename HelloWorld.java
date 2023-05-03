public class HelloWorld {

    public static int returnInteger(String text) {
        return Integer.parseInt(text);
    }


    public static void main(String[] args) {
        int num = returnInteger(args[0]);

        System.out.println(num);

        System.out.println("Hello World!");
    }
}