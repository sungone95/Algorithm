package a0324;

import java.util.*;
import java.io.*;

/*
 a n t i c -> 5글자는 모든 글자의 공통 
 따라서 5개보다 적게 가르칠수있으면 0출력 
 그 5개 이상이면 나머지 알파벳에서 순열 돌려서 
 모든 문자 확인 
 -> 앞에 anta, 뒤에 tica는 빼고 확인 해도됨 
 
 */


public class 백준1062가르침 {

	static String[] allword;
	static int moreteach;
	static int[] visit = new int[26];
	static int maxnum = 0;
	
	static int check() {
		int cnt = 0;
		for(int i=0; i<allword.length; i++) {
			String st = allword[i];
			int flag = 0;
			for(int j=4; j<st.length()-4; j++) {
				if(visit[st.charAt(j)-'a']==0) {
					flag = 1;
					break;
				}
			}
			if(flag==1)continue;
			else cnt++;
		}
		return cnt;
	}
	
	static void combination(int cnt, int idx) {
		
		if(cnt==moreteach) {
			int nowcnt = check();
			maxnum = Math.max(maxnum, nowcnt);
			return;
		}
		
		for(int i=idx; i<26; i++) {
			if(visit[i]==0) {
				visit[i] = 1;
				combination(cnt+1, i+1);
				visit[i] = 0;
			}
		}
		
	}
	
	
	public static void main(String[] args) throws Exception{
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer ST = new StringTokenizer(br.readLine());
		
		int wordnum = Integer.parseInt(ST.nextToken());
		int teachnum = Integer.parseInt(ST.nextToken());
		moreteach = teachnum-5;
		
		allword = new String[wordnum];
		
		for(int i=0; i<wordnum; i++) {
			allword[i] = br.readLine();
		}
		
		visit['a'-'a'] = 1;	visit['n'-'a'] =1;	visit['t'-'a'] = 1;	visit['i'-'a'] =1 ;	visit['c'-'a'] =1;
		
		
		if(moreteach < 0)System.out.println(0);
		else if(moreteach==21)System.out.println(wordnum);
		else {
			combination(0,0);
			System.out.println(maxnum);
		}
	
		
	}

}
