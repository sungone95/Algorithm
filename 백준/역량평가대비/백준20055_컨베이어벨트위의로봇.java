package a0324;

import java.util.*;
import java.io.*;

/*
 n,k 입력, 내구도가 0인칸이 k이상이면 종료 
 
 (벨트회전 -> 로봇 내릴수 있으면 내리기 -> 
 로봇이동(내구성1감소) -> 로봇 내릴수 있으면 내리기 -> 로봇올리기(내구성1감소)
 )
 -> 한세트
 
 구하는것 : 몇번째 세트에서 종료되는가?
 
 어떻게 구현?
 -> 벨트: 2차원 배열로 구현 
 -> 로봇: 1차원 배열로 위치 구현 
 */


public class 백준20055_컨베이어벨트위의로봇 {

	static int garo;
	static int k;
	static int[][] arr ;		//벨트의 내구성 
	static int[] robot ;			//로봇의 위치 
	
	public static void main(String[] args) throws Exception{
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		StringTokenizer ST = new StringTokenizer(br.readLine());
		garo = Integer.parseInt(ST.nextToken());
		k = Integer.parseInt(ST.nextToken());
		arr = new int[2][garo];
		robot = new int[garo];
		
		ST = new StringTokenizer(br.readLine());
		for(int i=0; i<garo; i++)arr[0][i]=Integer.parseInt(ST.nextToken());
		for(int i=garo-1; i>=0; i--)arr[1][i]=Integer.parseInt(ST.nextToken());
		
		int cnt = 1;
		
		while(true) {
//			System.out.println("cnt:" + cnt);
//			System.out.println("컨베이어벨트 이동");
			beltmove();			// 컨베이어벨트 이동
//			arrprint();
//			System.out.println();
//			robotprint();
//			System.out.println();
			
//			System.out.println("내릴수 있는 로봇 있으면 내리기");
			robotout();			// 내릴수 있는 로봇 있으면 내리기
//			arrprint();
//			System.out.println();
//			robotprint();
//			System.out.println();
			
//			System.out.println("로봇 이동가능한것만 한칸씩 이동");
			robotmove();		// 로봇 이동가능한것만 한칸씩 이동 
//			arrprint();
//			System.out.println();
//			robotprint();
//			System.out.println();
			
			//System.out.println("내릴수 있는 로봇 있으면 내리기");
			robotout();			// 내릴수 있는 로봇 있으면 내리기
//			arrprint();
//			System.out.println();
//			robotprint();
//			System.out.println();
			
			//System.out.println("로봇 올릴수 있으면 올리기");
			robotplus();		// 로봇 올릴수 있으면 올리기
//			arrprint();
//			System.out.println();
//			robotprint();
//			System.out.println();
			if(beltcheck() >= k)break;		// 벨트 내구성 전체 체크 
			cnt++;
		}
		System.out.println(cnt);
	}
	
	static void arrprint() {
		for(int i=0; i<2; i++) {
			for(int j=0; j<garo; j++) {
				System.out.print(arr[i][j]+" ");
			}
			System.out.println();
		}
	}
	
	static void robotprint() {
		for(int i=0; i<garo; i++) {
			System.out.print(robot[i]+" ");
		}
		System.out.println();
	}
	
	static int di[] = {1, 0, -1, 0};
	static int dj[] = {0, 1, 0, -1};
	
	static boolean check(int i, int j) {
		if(0<=i&&i<2 && 0<=j&&j<garo)return true;
		return false;
	}
	
	static void beltmove() {		//벨트의 이동 -> 로봇의 위치는 1씩 오른쪽, 벨트는 한칸씩
		int firstnum = arr[0][0];	//벨트이동을 위해 임의의 한곳 원소 저장 
		int d = 0;
		int nowi = 0;	int nowj = 0;
		int ni = 0;		int nj = 0;
		
		while(true) {
			ni = nowi+di[d];	nj = nowj+dj[d];
			if(check(ni, nj)) {					// 다음원소가 범위내에 있으면 옮겨
				arr[nowi][nowj] = arr[ni][nj];
				nowi = ni;	nowj = nj;
			}else {								// 범위내에 없으면 다음방향으로
				d = (d+1)%4;
			}
			if(ni==0 && nj==1)break;
		}
		arr[0][1] = firstnum;
		
		for(int i=garo-2; i>=0; i--) {			//벨트 이동에의한 로봇이동
			if(robot[i]==1) {
				robot[i+1]=1;
				robot[i] = 0;
			}
		}
	}
	
	static void robotout() {
		if(robot[garo-1]==1)robot[garo-1]=0;		//마지막 벨트위치에 있으면 내리기
	}	
	
	static void robotmove() {
		for(int i=garo-2; i>=0; i--) {			
			if(robot[i]==1 && arr[0][i+1]>=1 && robot[i+1]==0) {		//내구도 다음칸 1이상이면 이동
				robot[i+1]=1;
				robot[i] = 0;
				arr[0][i+1]--;			
			}
		}
	}
	
	static void robotplus() {
		if(arr[0][0] != 0 && robot[0]==0) {		//처음부분에 올릴수있으면 올리기
			robot[0] = 1;
			arr[0][0]--;
		}
	}
	
	static int beltcheck() {
		int cnt = 0;
		for(int i=0; i<2; i++) {
			for(int j=0; j<garo; j++) {
				if(arr[i][j]==0)cnt++;
			}
		}
		return cnt;
	}
}
