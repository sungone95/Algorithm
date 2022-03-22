package a0322;

import java.util.*;
import java.io.*;

/*
 union find 응용 하면 될듯?
 makeset, findset, unionset

 1) makeset -> 부모를 나타내는 배열 자신으로 초기화 
 2) unionset -> 각 배열에 자신의 직계 부모만 나타낸다 
 3) findset -> 배열에서 부모찾아가면서 부모가 같은지 비교 
 
 배열의 값 = idx 이면 -> 그 수는 자신이 제일 높은 부모 
 */


public class B2644촌수계산하기 {

	static int[] arr;
	static int num;
	static int upcnt;
	
	static void makeset() {
		for(int i=1; i<=num; i++) {
			arr[i]=i;
		}
	}
	
	static void unionset(int parent, int son) {
		arr[son] = parent;
	}
	
	static int findparent(int num) {
		
		if(arr[num] == num)return num;
		else {
			upcnt++;
			return findparent(arr[num]);
		}
	}
	
	
	public static void main(String[] args) throws Exception{
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		num = Integer.parseInt(br.readLine());	//사람수 
		arr = new int[num+1];
		makeset();
		
		StringTokenizer ST = new StringTokenizer(br.readLine());
		
		int p1 = Integer.parseInt(ST.nextToken());	//대상 1
		int p2 = Integer.parseInt(ST.nextToken());	//대상 2
		
		int rcnt = Integer.parseInt(br.readLine());	//관계수
		
		for(int i=0; i<rcnt; i++) {
			ST = new StringTokenizer(br.readLine());
			
			int num1 = Integer.parseInt(ST.nextToken());
			int num2 = Integer.parseInt(ST.nextToken());
			
			unionset(num1, num2);
		}
		
		upcnt = 0;
		int num1p = findparent(p1);
		int num1up = upcnt;
		
		upcnt = 0;
		int num2p = findparent(p2);
		int num2up = upcnt;
		int result = 0;
		
//		System.out.println(Arrays.toString(arr));
//		System.out.println("num1p:"+num1p+" num2p:"+num2p);
//		System.out.println("num1up:"+num1up+" num2up:"+num2up);
		if(num1p != num2p) {
			//System.out.println("num1p:"+num1p+" num2p:"+num2p);
			System.out.println(-1);
		}
		else {
			result += Math.abs(num1up-num2up);	//높이차 먼저 계산
			int nowp = 0;
			int tmpnum = 0;
			
			if(num1up > num2up) {
				tmpnum = p1;
				for(int i=0; i<num1up-num2up; i++) {
					nowp = arr[tmpnum];
					tmpnum = nowp;
				}
				if(nowp!=p2)result+=2;	//부모의 형제일때
				
			}else if(num1up < num2up) {
				tmpnum = p2;
				for(int i=0; i<num2up-num1up; i++) {
					nowp = arr[tmpnum];
					tmpnum = nowp;
				}
				if(nowp!=p1)result+=2;	//부모의 형제일때
				
			}else result+=2;			//서로 형제일때 
			
			System.out.println(result);
		}
		
		

	}
}
