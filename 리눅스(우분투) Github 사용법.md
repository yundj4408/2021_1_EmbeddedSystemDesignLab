# 리눅스(우분투) Github 사용법

#### 1. Git 설치

```
$ sudo apt-get install git-core
```



#### 2. Github 개인 정보 등록

```
$ sudo git config --global user.name "본인 계정 입력"
$ sudo git config --global user.email "본인 메일 주소 입력"
$ sudo git config --global color.ui "auto"
```



#### 3. 작업 폴더 생성

```
$ sudo mkdir /(이름)
$ cd /(이름)
```



#### 4. Github 저장소 복제

```
$ sudo git clone https://github.com/yundj4408/(repository 이름)
```



#### 5. 원격 저장소 등록

```
$ sudo git remote add origin https://github.com/yundj4408/(repository 이름)
$ sudo git fetch origin
```



#### 6. 변경된 모든 파일 추가 (커밋 전 필수 실행)

```
$ sudo git add -A
```



#### 7. 커밋

```
$ sudo git commit
```



#### 8. 커밋 메세지를 입력 (하지 않으면 커밋이 안된다)

```
$ sudo git commit -m "메세지 입력"
```



#### 9. 저장소에 올리기 (Github 계정과 암호 물어볼 것임)

```
$ sudo git push
```



#### 10. 저장소 업데이트 (내려받기)

```
$ sudo git pull
```



#### 11. Git 상태 확인

```
$ git status
```



출처 : https://emong.tistory.com/228