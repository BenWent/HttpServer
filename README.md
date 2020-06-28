# HttpServer
利用IO复用+非阻塞技术实现web集群，master利用http重定向将流量分散到slave服务器上

## 设计图

![设计图](</snapshot/设计图/设计图.png>)

## client 中的程序依赖关系

![设计图](</snapshot/设计图/客户端各源文件之间的关系.png>)

## master_sever 中的程序依赖关系

![设计图](</snapshot/设计图/主服务器各源程序之间的关系.png>)

## slave_sever 中的程序依赖关系

![设计图](</snapshot/设计图/从服务器各源程序之间的关系.png>)