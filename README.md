# GameTeam
팀프로젝트 DirectX 3D

## Pull 한 이후 빌드가 안될시
 * 32Bit 가 맞는지 확인
## ReadMe
1. 클라는 엔진 참조 걸어서 **엔진 내용이 바뀌면** 자동으로 엔진빌드
2. 엔진이 빌드되면 헤더와 바이너리 파일들 자동으로 클라로 옮김 ***(Bat 파일 실행 시킬 필요 X)***
3. PDB 파일도 옮겨서 엔진코드도 디버깅 가능
4. 복사 생성자 삭제 이후에  가상함수를 새로 정의 CloneEventAddRef ?? =>  소유권을 서로 공유하는 포인터들 Clone  AddRef 하는 코드 규칙 이며 이 함수는 Clone 에서 반드시 호출.
