# Rocks-JSJ

![image](https://user-images.githubusercontent.com/28651727/128209219-d5c67298-fa7a-44c0-a3e6-06fea3b1cf03.png)

## AWS인스턴스 Kafka설치

## AWS 인스턴스에서

### 1. AWS EC2인스턴스 생성

1. 보안그룹 -> 인바운드 규칙
   - 2181 포트 개방 : 주키퍼 기본 포트
   - 9092 포트 개방 : 카프카 브로커 기본포트
2. 인스턴스 접속


### 2. 인스턴스 자바 설치(jdk-11)
```
sudo apt-get install openjdk-11-jdk
java --version
```
### 3. 카프카 브로커 다운로드
```
wget https://archive.apache.org/dist/kafka/2.8.0/kafka_2.13-2.8.0.tgz
tar xvf kafka_2.13-2.8.0.tgz
```

### 4. 카프카 브로커 설정

**힙메모리 설정**

카프카 브로커의 경우 힙메모리가 1Gb, 주키퍼의 경우 512Mb로 기본 설정되어있다.  
만약 메모리가부족하면 `Cannot allocate memory`에러가 출력되면서 실행되지 않는다.

이때 환경변수를 통해 힙메모리를 지정해 줄 수 있다.

```
export KAFKA_HEAP_OPTS="-Xmx400m -Xms400"
echo $KAFKA_HEAP_OPTS
```

**실행옵션 설정**
config폴더의 server.properties파일에는 카프카 브로커가 클러스터운영에 필요한 옵션들을 지정할 수 있다.

advertised.listeners의 주석을 해제하고 aws인스턴스의 퍼블릭 IPv4 주소를 적는다.

```
...
advertised.listeners=PLAINTEXT://**<AWS인스턴스주소>**:9092
...
```

### 5. 주키퍼 실행
카프카 바이너리 폴더에 주키퍼가 준비되어있다.

```
bin/zookeeper-server-start.sh -daemon config/zookeeper.properties
```

`-daemon`옵션을 해제하면 포그라운드에서 실행하여 주키퍼 로그를 확인할 수 있다.


### 6. 카프카 브로커 실행

```
bin/kafka-server-start.sh -daemon config/server.properties
```

## 로컬 컴퓨터에서

### 카프카 서버와 통신 확인

카프카 바이너리 패키지는 카프카 브로커에 대한 정보를 가져올 수 있는 `kafka-broker-api-versions.sh`명령어를 제공한다. 이명령어를 통해 카프카 브로커와 정상적으로 연동되는지 확인할 수 있다.

로컬에도 동일하게 kafka를 다운로드한다.
```
wget https://archive.apache.org/dist/kafka/2.8.0/kafka_2.13-2.8.0.tgz
tar xvf kafka_2.13-2.8.0.tgz
```

통신 확인
```
bin/kafka-broker-api-versions.sh --bootstrap-server <AWS 인스턴스 주소>:9092
```

