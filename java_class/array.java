
public class array {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		int [][] myarray = {
				
				{1,2,3,4,5,6,7,8,9,10},
				{27}
			};
		
		int i=0;
		int j=0;
		while(j<2){
			i=0;
			while(i<10)
			{
				System.out.println(i + " :        " + myarray[j][i]);
				i++;
			}
		j++;
		}
		// TODO Auto-generated method stub

	}

}
