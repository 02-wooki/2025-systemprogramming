# 🛠️ 리눅스 명령어 C 언어 구현 목록 및 설명

각 명령어는 실제 리눅스 명령어와 유사한 동작을 하며, 주요 옵션들도 함께 구현되어 있습니다. (옵션 포함 총 50개)

---

## 📤 echo (2)

문자열을 출력합니다. 환경변수나 리디렉션 사용 가능.

| 명령어 예시           | 설명                                |
|------------------------|-------------------------------------|
| `echo [텍스트]`        | 텍스트를 출력                       |
| `echo -n [텍스트]`     | 줄바꿈 없이 출력                    |

---

## 📁 pwd (1)

| 명령어 예시 | 설명                    |
|-------------|-------------------------|
| `pwd`       | 현재 디렉토리의 전체 경로를 출력 |

---

## 🕒 date (3)

| 명령어 예시           | 설명                                      |
|------------------------|-------------------------------------------|
| `date`                 | 현재 날짜와 시간 출력                     |
| `date -d "[날짜]"`     | 지정한 날짜를 기준으로 출력               |
| `date +"[포맷]"`       | 포맷 문자열에 따라 날짜 형식 지정 출력   |

---

## 📄 cat (11)

파일 내용을 출력합니다. 여러 파일 연결도 가능.

| 명령어 예시                          | 설명                                      |
|--------------------------------------|-------------------------------------------|
| `cat`                                | 파일 내용 출력                            |
| `cat -b`                             | 비어 있지 않은 줄에 번호 부여             |
| `cat -n`                             | 모든 줄에 번호 부여                       |
| `cat -s`                             | 연속된 빈 줄을 하나로 축약                |
| `cat -E`                             | 줄 끝에 `$` 기호 표시                     |
| `cat -A`                             | 제어 문자 표시 (줄 끝 포함)               |
| `cat --number-nonblank` (`-b`)       | 비어 있지 않은 줄에 번호 부여             |
| `cat --number` (`-n`)                | 모든 줄에 번호 부여                       |
| `cat --squeeze-blank` (`-s`)         | 연속된 빈 줄 압축                         |
| `cat --show-ends` (`-E`)             | 줄 끝 `$` 표시                            |
| `cat --show-all` (`-A`)              | 모든 숨겨진 문자와 줄 끝 표시             |
| ※ 단일 문자 옵션은 축약 가능 (`-bsE`) |

---

## 👤 whoami (1)

| 명령어 예시 | 설명                        |
|-------------|-----------------------------|
| `whoami`    | 현재 로그인한 사용자 이름 출력 |

---

## 👥 id (1)

| 명령어 예시 | 설명                                       |
|-------------|--------------------------------------------|
| `id`        | 사용자 ID, 그룹 ID, 그룹 리스트 출력       |

---

## 📂 ls (13)

디렉토리 내 파일 목록 출력.

| 명령어 예시      | 설명                                 |
|------------------|--------------------------------------|
| `ls`             | 파일 및 디렉토리 목록 출력           |
| `ls -a`          | 숨김 파일 포함 전체 목록 출력        |
| `ls -l`          | 자세한 정보 출력 (권한, 소유자 등)  |
| `ls -h`          | 사람이 읽기 쉬운 파일 크기 출력      |
| `ls -r`          | 역순 출력                             |
| `ls -S`          | 크기 기준 정렬                       |
| `ls -t`          | 수정 시간 기준 정렬                  |
| `ls -A`          | `.` 및 `..` 제외한 숨김 파일 포함 출력 |
| `ls -b`          | 특수 문자 이스케이프 처리            |
| `ls -i`          | 아이노드 번호 함께 출력              |
| `ls -I <패턴>`   | 지정한 패턴 파일 제외                |
| `ls -L`          | 심볼릭 링크를 실제 파일로 처리        |
| `ls -m`          | 콤마로 구분된 나열 출력              |

---

## 🏗️ mkdir (3)

디렉토리 생성 명령어.

| 명령어 예시         | 설명                                |
|----------------------|-------------------------------------|
| `mkdir`              | 디렉토리 생성                      |
| `mkdir -m <권한>`    | 생성 시 권한 설정                   |
| `mkdir -p`           | 상위 디렉토리까지 재귀적으로 생성  |

---

## 🗑️ rmdir (1)

| 명령어 예시 | 설명                              |
|-------------|-----------------------------------|
| `rmdir`     | 비어 있는 디렉토리 삭제           |

---

## 📅 touch (5)

파일 생성 또는 타임스탬프 변경.

| 명령어 예시          | 설명                                        |
|-----------------------|---------------------------------------------|
| `touch`               | 파일 생성 또는 수정 시간 갱신              |
| `touch -c`            | 파일이 없으면 생성하지 않음                |
| `touch -a`            | 접근 시간만 변경                           |
| `touch -m`            | 수정 시간만 변경                           |
| `touch -t [[CC]YY]MMDDhhmm[.ss]` | 지정한 시간으로 타임스탬프 설정     |

---

## ⏱️ sleep (1)

| 명령어 예시 | 설명                       |
|-------------|----------------------------|
| `sleep N`   | N초 동안 대기               |

---

## 🧱 basename (1)

| 명령어 예시        | 설명                                  |
|---------------------|---------------------------------------|
| `basename /a/b/c.txt` | 경로에서 `c.txt` 부분만 추출         |

---

## 📌 dirname (1)

| 명령어 예시        | 설명                                |
|---------------------|-------------------------------------|
| `dirname /a/b/c.txt` | 경로에서 디렉토리 경로 `/a/b` 추출 |

---

## 📥 head (3)

파일의 **처음 부분**을 출력.

| 명령어 예시        | 설명                              |
|---------------------|-----------------------------------|
| `head`              | 처음 10줄 출력                    |
| `head -n N`         | 처음 N줄 출력                     |
| `head -c N`         | 처음 N바이트 출력                 |

---

## 📤 tail (3)

파일의 **끝 부분**을 출력.

| 명령어 예시        | 설명                              |
|---------------------|-----------------------------------|
| `tail`              | 마지막 10줄 출력                  |
| `tail -n N`         | 마지막 N줄 출력                   |
| `tail -c N`         | 마지막 N바이트 출력               |

---

📦 이 문서는 리눅스 명령어를 C 언어로 직접 구현한 프로젝트에 대한 요약입니다.  
각 명령어 파일은 POSIX 규격을 기반으로 하고 있으며, 주요 기능 및 옵션을 반영해 구현되었습니다.
