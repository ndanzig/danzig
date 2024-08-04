
public class MyString {
	public static void main(String[] args) {
		

String one="hi mom ";
System.out.println(one + one );

//String str = "abc";

char data[] = {'a', 'b', 'c'};
String str = new String(data);


System.out.println("abc");
String cde = "cde";
System.out.println("abc" + cde);

String c = "abc".substring(2,3);
String d = cde.substring(1, 2);

System.out.println(c + d);
//see http://java.sun.com/j2se/1.4.2/docs/api/java/lang/String.html


char []newArray = cde.toCharArray();

System.out.println(newArray[1]);

String e = "Too many cooks spoil the broth";
cde=e.replaceAll("oo", "he");
 System.out.println(cde);
 System.out.println(e);




	}

}
