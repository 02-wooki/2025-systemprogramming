# 4월 11일 수업내용

## 1. 초기 환경 설정 및 기본 명령어 학습
- 가상 머신 설치 (VirtualBox, Ubuntu)
- 기본 명령어 학습: `pwd`, `ls`, `cd`, `mkdir`, `rmdir`, `cp`, `mv`, `rm`, `cat`, `more`, `less`
- 사용자 및 그룹 관리: `adduser`, `usermod`, `passwd`, `groups`
- 파일 권한 및 소유자 설정: `chmod`, `chown`, `umask`

## 2. 시스템 관리 및 프로세스 제어
- 프로세스 확인 및 제어: `ps`, `top`, `htop`, `kill`, `nice`, `renice`
- 서비스 관리: `systemctl`, `service`, `journalctl`
- 패키지 관리: `apt`, `dpkg`, `snap`
- cron 및 at을 이용한 작업 스케줄링

## 3. 파일 시스템 및 디스크 관리
- 파일 시스템 구조 이해
- 디스크 용량 확인 및 관리: `df`, `du`, `mount`, `umount`, `lsblk`, `fdisk`
- 파일 검색 명령어: `find`, `locate`, `which`, `whereis`

## 4. 네트워크 기초
- 네트워크 설정 확인: `ip`, `ifconfig`, `netstat`, `ss`, `ping`, `traceroute`
- 포트와 프로세스 확인: `lsof`, `nmap`, `netcat`

## 5. bash 쉘 스크립트
- 변수 선언, 제어문 (`if`, `for`, `while`)
- 사용자 입력 및 출력 처리
- 스크립트 실행 권한 부여 (`chmod +x`)

## 6. 기타 유틸리티 및 시스템 사용성 향상 도구
- `alias`, `history`, `.bashrc` 설정
- 파일 압축 및 해제: `tar`, `gzip`, `zip`, `unzip`
- 파일 비교 및 처리: `diff`, `cmp`, `sort`, `uniq`, `cut`, `awk`, `sed`
# 수업 내용 요약 – 리눅스 시스템 관리 및 실습 (2025.03.07 ~ 06.07)

## 1. 리눅스 설치 및 환경 구성
- VirtualBox를 사용한 Ubuntu Server 설치
- 네트워크 브리징 설정 및 초기 계정 구성
- SSH 서버 설치 및 접속 설정 (`openssh-server`, `ssh`)
- 호스트명 변경과 `/etc/hosts` 설정
- 정적 IP 설정을 통한 원격 접속 유지

## 2. 리눅스 기본 명령어 및 파일 시스템
- 경로 확인 및 이동: `pwd`, `cd`
- 디렉토리 및 파일 조작: `ls`, `mkdir`, `rmdir`, `touch`
- 파일 내용 확인: `cat`, `more`, `less`, `head`, `tail`
- 복사, 이동, 삭제: `cp`, `mv`, `rm`
- 숨김 파일 및 파일 패턴(`*`, `?`, `[]`) 이해

## 3. 사용자 및 그룹 관리
- 사용자 추가 및 수정: `adduser`, `useradd`, `usermod`
- 비밀번호 변경: `passwd`
- 그룹 추가 및 관리: `groupadd`, `groupmod`, `groupdel`, `gpasswd`
- `/etc/passwd`, `/etc/group`, `/etc/shadow` 파일 구조 분석

## 4. 파일 권한 및 접근 제어
- 퍼미션 구조 이해: 읽기(r), 쓰기(w), 실행(x)
- `chmod`를 통한 퍼미션 변경 (기호식, 8진수 방식)
- `chown`, `chgrp`를 통한 소유자 변경
- 기본 umask 설정 확인 및 변경 (`umask`)
- 접근 제어 리스트(ACL) 개념 소개

## 5. 프로세스 관리
- 프로세스 상태 확인: `ps`, `top`, `htop`, `pidof`
- 백그라운드 작업 처리: `&`, `jobs`, `fg`, `bg`
- 강제 종료 및 우선순위 설정: `kill`, `killall`, `nice`, `renice`
- 부팅 시 자동 실행 관리: `systemd`, `systemctl`, 서비스 등록 및 상태 확인

## 6. 디스크 및 파일 시스템 관리
- 디스크 마운트 및 언마운트: `mount`, `umount`
- 파일 시스템 정보 확인: `df`, `du`, `lsblk`, `blkid`, `fdisk`
- 하드링크와 심볼릭 링크: `ln`, `ln -s`의 차이점
- 파일 및 디렉토리 검색: `find`, `locate`, `which`, `whereis`

## 7. 네트워크 명령어 및 설정
- 네트워크 설정 확인: `ip a`, `ip r`, `hostname`, `ping`
- 연결 상태 확인: `netstat`, `ss`, `lsof`, `nmap`
- 포트 테스트 및 TCP 연결: `telnet`, `nc`, `curl`
- DNS 확인 및 호스트 설정: `/etc/hosts`, `dig`, `nslookup`

## 8. 스케줄링 및 작업 자동화
- cron 작업 등록: `crontab -e`, crontab 파일 구조 (`분 시 일 월 요일`)
- at 명령어를 통한 단발성 작업 예약
- cron 로그 확인 및 관리 (`/var/log/syslog`, `systemctl status cron`)

## 9. 패키지 및 업데이트 관리
- APT 패키지 시스템 개요: `apt update`, `apt upgrade`, `apt install`
- 패키지 검색 및 삭제: `apt search`, `apt remove`, `apt purge`
- `.deb` 파일 설치: `dpkg -i`
- snap을 통한 컨테이너형 앱 설치

## 10. Bash 쉘 및 스크립트 프로그래밍
- bash 환경 변수: `$HOME`, `$USER`, `$PATH`, `$PWD`
- 변수 선언 및 출력: `VAR=value`, `echo $VAR`
- 제어문 활용: `if`, `case`, `for`, `while`
- 사용자 입력 처리: `read`, `echo`
- 조건식 및 비교 연산자: `-eq`, `-ne`, `-lt`, `==`, `!=`
- 스크립트 파일 실행: `chmod +x`, `./script.sh`
- `#!/bin/bash` 해석기 지정 및 exit 코드

## 11. 시스템 로그 및 보안
- 로그 확인: `dmesg`, `journalctl`, `/var/log/syslog`, `/var/log/auth.log`
- 사용자 활동 추적 및 감시 방법
- 파일 접근 로그 및 `last`, `who`, `w` 명령어

## 12. 기타 유용한 유틸리티 명령어
- 파일 비교 및 조작: `diff`, `cmp`, `comm`, `cut`, `paste`
- 텍스트 처리 도구: `sort`, `uniq`, `awk`, `sed`, `tr`
- 압축 및 아카이브: `tar`, `gzip`, `gunzip`, `zip`, `unzip`
- 셸 설정 파일: `.bashrc`, `.profile`, `alias`, `history`