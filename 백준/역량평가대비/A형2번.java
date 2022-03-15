package a0315;
import java.util.*;
import java.io.*;

/*
 (1,1)에서 시작 -> 이동거리 최소값을 구하라 
 규칙 -> 해당 벌레 잡고 해당벌레번호표시된곳으로 갈수있음 
 바로갈 필요 X, 
 
 이동가능한 좌표의 리스트를 파라미터로 넘겨주면서 완전탐색 한다 
 거리는 현재위치 ~ 리스트에서 선택된 좌표 
 dfs리턴시점 -> 리스트 사이즈가 0일때 -> move길이 비교 
 
 */






public class A형2번 {

	static int[][] arr;
	static int size;
	static int minmove;
	
	static int[][] people;
	
	static void move(int i, int j, int movelen, ArrayList<int[]> list) {
		
		//System.out.println("nowi:"+i+" nowj:"+j);
		
		if(list.size()==0) {
			minmove = Math.min(movelen, minmove);
			return;
		}
		
		
		
		for(int idx=0; idx<list.size(); idx++) {
			int[] now = list.get(idx);
			int nowi = now[0];	int nowj = now[1];
			int nownum = arr[nowi][nowj];	//좌표상에 써있는 번호
			
			int nowmove = Math.abs(i-nowi)+Math.abs(j-nowj);	//지금 움직인 거리
			
			ArrayList<int[]>tmplist = new ArrayList<>();	//파라미터로 쓸 임시 리스트
			for(int k=0; k<list.size(); k++) {
				tmplist.add(list.get(k));
			}
			
			if(nownum>0) {				//몬스터인경우 의뢰인 추가
					
				tmplist.remove(idx);
				int peoplei = people[nownum][0];
				int peoplej = people[nownum][1];
				tmplist.add(new int[] {peoplei, peoplej});
			}else {						 
				tmplist.remove(idx);
			}
			
			move(nowi, nowj, movelen+nowmove, tmplist);
			
		}
		
	}
	
	
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int tc = Integer.parseInt(br.readLine());
		
		for(int t=1; t<=tc; t++) {
			size = Integer.parseInt(br.readLine());
			arr = new int[size][size];
			people = new int[5][2];
			
			ArrayList<int[]> canmove = new ArrayList<>(); 	//움직일수있는곳
			minmove = Integer.MAX_VALUE;
			
			for(int i=0; i<size; i++) {
				StringTokenizer ST = new StringTokenizer(br.readLine());
				for(int j=0; j<size; j++) {
					arr[i][j] = Integer.parseInt(ST.nextToken());
					if(arr[i][j] > 0) {
						canmove.add(new int[] {i,j});	//몬스터 좌표들 이동가능지역으로 입력
					}else if(arr[i][j]<0) {
						people[-1*arr[i][j]][0] = i;
						people[-1*arr[i][j]][1] = j;
					}
				}
			}
			
			//------ 완료 -------
			
			move(0, 0, 0, canmove);
			System.out.print("#"+t+" ");
			System.out.println(minmove);
		}
		
		
	}

}
