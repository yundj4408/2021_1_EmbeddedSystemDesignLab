[임베디드시스템설계실험]

## 1주차





## [2주차] 2021년 03월 11일 

### 1. Markdown에 관하여

### 	1.1 Markdown이란?

​		Markdown은 웹상에서 글을 쓰는 사람들을 위한 글쓰기 도구(서식, 포맷, ,양식)이다.

​		마크다운 (Markdown)은 [마크업 언어](https://namu.wiki/w/마크업 언어)의 일종으로, 존 그루버와 아론 스워츠가 만들었다. 

​		온갖 태그로 범벅된 HTML 문서 등과 달리, 읽기도 쓰기도 쉬운 문서 양식을 지향한다.



### 	1.2 Markdowm를 사용하는 이유

​		1. HTML 경험이 없는 사람도 누구나 쉽게 쓰고 읽을 수 있다. 

​		2. 여러 기기에서 사용하기 편하다. 

​		3. 여러 기기나 장치를 오가도 서식이 망가지는 경우가 없다.

​		4. 다양한 스타일을 적용하는게 정말 쉽다. 



### 2. Vim

### 	2.1 Vim이란? 또 사용해야하는 이유?

​		Linux의 대표적인 편집기인 vi와 호환되는 텍스트 편집기이다.

​		Vim에 대해서 알아야하는 이유는 임베디드 OS로 Linux를 많이 사용하고 있다.

​		그럼 여기서도 의문인게 **왜??? 도대체 왜???** **임베디드 OS로 Linux를 사용하는가?**

​		그 이유로는 Linux는 개발 비용이 크게 단축되고, 많은 솔루션들이 Open Source 형태로 제공이 

​		되어개발 기간 또한 단축되어 개발에 유리하기 때문이다. 



### 2.2 Vim Interface의 종류

​		Vim Interface는 총 2가지가 있는데, CUI(Command User Interface)를 사용한 전통적인 

​		텍스트 모드와 GUI(Graphic User Interface)를 사용한 GVim이 있다. 

​		설치하는 방법은 아래와 같다.

```
sudo apt-get install vim
sudo apt-get install gvim
```

​		sudo apt-get install gvim을 하였을때 오류가 뜨는 경우가 있다. 

### 2.3 Vim Script란?

​		Vim Script는 vim 명령들을 자동으로 처리하도록 작성한 vim용 명령어이다. 

​		.vimrc는 기본적으로 vim을 시작하게 되면 로드하게 되는 script 파일이다. 

​		(다른 vim script는 vim을 사용해보면서 추가하겠다. )

​		.vimrc 파일은 시스템마다 로드하는 위치와 순서가 다르다.

​		밑의 커맨드를 통해 운영체제 마다 어디에 저장되는지 알 수 있다. 

```vim script
:help vimrc
```

```
The user vimrc files(s):
		 "$HOME/.vimrc"					(for Unix and OS/2) (*)
		 "$HOME/.vim/vimrc"				(for Unix and OS/2) (*)
		 "$s:.vimrc"					(for Amiga) (*)
		 "$home:.vimrc"					(for Amiga) (*)
		 "$home:vimfiles:vimrc"			(for Amiga) (*)
		 "$VIM/.vimrc"					(for OS/2 and Amiga) (*)
		 "$HOME/_vimrc"					(for MS-DOS and Win32) (*)
		 "$HOME/vimfiles/vimrc"			(for MS-DOS and Win32) (*)
		 "$VIM/_vimrc"					(for MS-DOS and Win32) (*)

```

​		vim에 대해서 궁금한 것이 생기면 :help something을 활용하자. 

​		필자는 Ubuntu를 사용하고 있다. vimrc파일을 수정하기 위해선 2가지 방법이 있다.

​		1. home directory에 cd 커멘드를 통해 접근하여 vim .vimrc 

​		2. vim 안에서 :e ~/.vimrc를 치면 바로 .vimrc파일이 열린다. 

​		

(vimrc 설정 명령어)

| **설정 값**                                  | **설명**                                                 |
| -------------------------------------------- | -------------------------------------------------------- |
| syntax on                                    | Syntax highlight                                         |
| colorscheme desert                           | vi 테마, 찾아보면 다양한 color scheme들이 있다.          |
| set background=dark                          | 배경 색상                                                |
| set encoding=utf-8                           | utf-8을 표준 인코딩으로 설정                             |
| set fileencodings=utf=8,euc-kr,ucs-bom,cp949 | 파일인코딩 형식 지정                                     |
| set nobackup                                 | Backup file을 만들지 않음                                |
| set noswapfile                               | swap file을 만들지 않음                                  |
| set title                                    | 제목을 표시                                              |
| set nowrap                                   | Line이 길어서 화면을 넘어가는 경우 자동 줄바굼 하지 않음 |
| set wrap                                     | Line이 길어서 화면을 넘어가는 경우 자동 줄바꿈           |
| set mouse=a                                  | Use mouse or not                                         |
| set ruler                                    | 오른쪽 하단에 현재 위치 표시                             |
| set history=1000                             | vim에서 기억할 history line 수                           |
| set hlsearch                                 | 검색 결과 강조                                           |
| set ignorecase                               | 검색시 대소문자 구분하지 않음                            |
| set incsearch                                | 글자 입력될 때마다 같은 부분 표시                        |
| set showmatch                                | 현재 커서가 놓여진 괄호 쌍 표시                          |
| set foldmethod=indent                        | Syntaxx에 따라 접어두기, 열기(zo) 접기(zc)               |
| set foldnestmax=1                            | Fold시 최대 깊이 1                                       |
| set expandtab                                | tab 대신 띄어쓰기로                                      |
| set nocompatible                             | 방향키로 이동 가능                                       |
| set bs=indent,eol,start                      | backspace 키 사용 가능                                   |
| set wmnu                                     | tab 자동 완성시 가능한 목록을 보여줌                     |
| set number                                   | line number를 표시해준다.                                |
| set autoindent                               | 자동 들여쓰기                                            |
| set smartindent                              | Syntax 고려해서 들여쓰기                                 |
| set cindent                                  | C style indent                                           |
| set ts=4                                     | 탭을 4칸으로, 1 tab=4 spaces                             |
| set shiftwidth=4                             | 자동 들여쓰기 4칸                                        |



​		필자의 .vimrc파일 Setting이다. 		
​	​![vimrcSetting](./Pictures/vimrcSetting.JPG)













### 2.4 Vim 모드

​		**1.** **Normal Mode(Command Mode) :** 일반/명령 모드

​		일반 모드는 키 입력을 통해 vim에 명령을 내리는 모드이다.

​		커서를 이동하거나 삭제, 복사, 붙여넣기 등의 작어을 수행 할수 있다. 

​		vim은 다른 editer와 다르게 일반 모드로 실행이 되기 때문에 바로 편집이 불가능하다.



​		**2. Insert Mode :** 입력/편집 모드

​		입력 모드는 실제로 문서를 편집하기 위한 모드이다.

​		다른 에디터의 기본 모드와 같다고 보면 된다.



​		**3. Visual Mode :** 비주얼 모드

​		vim에서 대부분의 명령을 수행할 때에는 범위를 지정할 수 있는데, 

​		문서 전체를 지정하거나 특정 행 또는 특정 행으로부터 N개의 행 등 다양한 방법으로

​		범위를 지정할 수 있다. 

​		

​		4. **Command-line Mode : **명령라인 모드

​		명령라인 모드는 명령 입력으로 여러 가지 일을 수행할 수 있는 모드이다. 

​		vim의 설정을 바꾸거나 파일 저장, 파일 이름 수정 등 여러가지 기능들이 있다.

​		

​		모드 변경은 밑에 있는 그림을 참고하면 된다. 

------

![VimMode](./Pictures/VimMode.JPG)



### 2.5 Vim 명령어

​		VIm명령어 중 자주 쓰이고 필수로 알고 있어야 하는 명령어들을 정리해보겠다.



​		**<입력>**

| Key  | Action                              | Key  | Action                            |
| ---- | ----------------------------------- | ---- | --------------------------------- |
| a    | 커서에 위치 다음 칸 부터 입력       | A    | 커서에 행의 맨 마지막부터 입력    |
| i    | 커서에 위치에서 입력                | I    | 커서에 맨 앞에서부터 입력         |
| o    | 커서에 다음 행에서 입력             | O    | 커서에 이전 행에서 입력           |
| s    | 커서에 위치한 한 글자를 지우고 입력 | cc   | 커서에 위치의 한 행을 지우고 입력 |



​		**<저장 & 종료 & 불러오기>**

| Key           | Action                            | Key        | Action             |
| ------------- | --------------------------------- | ---------- | ------------------ |
| w             | 저장                              | w file.txt | file.txt로 저장    |
| w >> file.txt | file.txt파일에 덧붙여 저장        | zz         | Vim 저장하고 종료  |
| q!            | Vim 강제 종료                     | q          | Vim 종료           |
| wq!           | Vim 강제로 저장하고 강제 종료     | wq         | VIm 저장하고 종료  |
| e file.txt    | file.txt 파일 불러오기            | e          | 현재 파일 불러오기 |
| VIm           | 이전에 작업한 프로젝트로 들어가기 |            |                    |

​		

​	**<복사 & 붙여넣기 & 삭제>**

| Key   | Action                             | Key   | Action                            |
| ----- | ---------------------------------- | ----- | --------------------------------- |
| yy    | 현재 커서에 있는 행 복사           | p     | 붙여넣기                          |
| [?]yy | 커서가 있는 행부터 ? 까지 복사     | [?]p  | ?번 만큼 붙여넣기                 |
| x, dl | 커서에 위치한 글자 삭제            | X, dh | 커서 앞에 글자 삭제               |
| dw    | 한 단어 삭제                       | d0    | 커서의 위치부터행의 처음까지 삭제 |
| D, d$ | 커서 위치부터 행 끝까지 삭제       | dd    | 커서가 위치한 행 삭제             |
| dj    | 커서가 있는 행과 그 다음 행을 삭제 | dk    | 커서가 있는 행과 그 앞의 행 삭제  |



### 3. gcc명령어

​		**[gcc 컴파일]**

​		1. gcc 파일명(*.c) : Default로 out 파일이 생성된다. (ex. a.out)

​		2. gcc -c 파일명(*.c) : Object 파일을 생성한다. 

​		3. gcc -c 오브젝트_파일명(.o) 파일명(.c) 

​			gcc -o 실행파일명 (*.out) 오브젝트_파일명(*.o)

​		4. gcc -o 실행파일 파일명(*.c) : 실행 파일을 만든다. (3번을 한줄로)



### 4. Makefile

​		Makefile을 사용하는 이유는 컴파일할때 위와 같은 복잡한 과정을 생략할 수 있어서이기도 하지만, 

​		Makefile이 제공하는 강력한 기능중 하나인 **Incremental build**를 사용하기 위해서이다.



​		**Incremental build** 란?

​		반복적인 빌드 과정에서 변경된 소스 코드에 의존성이 있는 대상들만 추려서 다시 빌드하는 기능이다.



​		밑의 사진은 기본적인 makefile

![MakefileNormalSetting](./Pictures/Makefile.JPG)

​		make를 통해 만든 object를 한번에 삭제하는 명령어는 `rm -rf *.o` 이다. 



### 5. SAMBA란?

​		리눅스 서버에서 올려놓은 파일을 윈도우에서 사용하고 싶을때 사용하는 일종의 공유 폴더라고 생각하면 		된다. 프로토콜은 SMB(Server Message Block)를 사용한다. 



​		**1. 삼바 설치**

​		`apt-get install -y samba //우분투의 경우`

​		`yum instasll -y samba //centOS일 경우`

![Samba](./Pictures/Samba.JPG)



​		

​		**2. 삼바 계정 추가하기 - smbpasswd 명령어**

​		`smbpasswd -a username`

​		명령어의 **<계정명>** 부분은 실제 계정 이름을 입력하면 된다.

​		![samba 계정생성](./Pictures/SambaAccount.JPG)

​		

​		**3. 삼바 공유할 디렉토리 설정**

​		`sudo nano /etc/samba/smb.conf `

​		공유할 디렉토리를 설정하기 위해서 설정 파일의 가장 하단에 아래와 같은 형태로 입력한다.

​		[multimedia]부터 적어주면 된다. 

​		![SambaShareDirectoryCreate](./Pictures/SambaShareDirectoryCreate.JPG)

​		create mode와 directory mode는 실제 필요한 권한만 주는 것도 가능하다.

​		Read는 4, Write는 2, Execute는 1이며 모든 권한을 주기 위해 777을 사용했다.

​		읽기 전용으로 변경하려면 writeble과 read only 값을 각각 no, yes로 변경하면 된다.



​		**4. Samba 재시작**

​		파일 수정이 완료하고 저장하면 Samba를 재시작 해주면 된다.

​		`sudo service smbd restart`

​		

​		**5. VirtualBox사용을 위한 Setting (가상 머신을 사용하지 않는다면 Host Only Network 과정 생략)**

​		`host -I`를 통해 우분투 IP를 확인하고, 윈도우에서 Windows Key+ R키를 눌러 실행창을 열고 

​		그 IP를 넣어준다.

​		(필자는 VirtualBox를 사용하기 때문에 가상머신의 IP를 넣으니 아무 일도 일어 나지 않았다. )

​		아무 것도 건드리지 않고 Virtualbox에서 우분투 가상 머신을 만들 경우, NAT 형태의 네트워크가 우분투에

​		기본으로 잡히게 된다. 그런데, 이 NAT형태의 네트워크를 통해 호스트 머신으로 삼바 공유를 하는 것은 좀 

​		어렵다고 한다. 그래서 Host Only Network를 만들어 사용하였다. 



​		먼저 가상머신을 종료 후 가상머신 창의 **Machine->Setting->Network**로 간다. 

​						![Host-only Adapter 추가](./Pictures/Host-onlyAdapter.JPG)	

​		그림에서 보이는 것처럼 Adapter1은 보통 NAT로 들어가 있으므로, 

​		Adapter2에 네트워크를 하나 추가한다. 

​		"Enable Network Adapter"를 체크하고 "Attached to" 항목에 Host-only Adapter를 선택한다. 

​		이 세팅을 완료하고 우분투에서 `hostname -I` 사용한다면 2개의 IP가 나올것이다. 





​		![hostname](./Pictures/hostname.JPG)

​		그림에서 보이는 2개의 IP중, 192.168.~.~를 윈도우에서 Windows Key+ R키를 눌러 실행창을 열고 넣어 

​		준다.



​		![WindowSamba](./Pictures/WindowSamba.JPG)

​		다음 화면이 뜨면 우분투에서 설정해준 사용자 이름과 암호를 입력하여 확인 버튼을 누르면 우분투의 파일		을 쉽게 window로 들고 올 수 있다.

​		

