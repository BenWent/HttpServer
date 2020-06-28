# HttpServer
利用IO复用+非阻塞技术实现web集群，master利用http重定向将流量分散到slave服务器上

## 设计图

![设计图](<[https://github.com/BenWent/HttpServer/blob/master/snapshot/%E8%AE%BE%E8%AE%A1%E5%9B%BE/%E8%AE%BE%E8%AE%A1%E5%9B%BE.png](https://github.com/BenWent/HttpServer/blob/master/snapshot/设计图/设计图.png)>)

## client 中的程序依赖关系

![设计图](<[https://github.com/BenWent/HttpServer/blob/master/snapshot/%E8%AE%BE%E8%AE%A1%E5%9B%BE/%E5%AE%A2%E6%88%B7%E7%AB%AF%E5%90%84%E6%BA%90%E6%96%87%E4%BB%B6%E4%B9%8B%E9%97%B4%E7%9A%84%E5%85%B3%E7%B3%BB.png](https://github.com/BenWent/HttpServer/blob/master/snapshot/设计图/客户端各源文件之间的关系.png)>)

## master_sever 中的程序依赖关系

![设计图](<[https://github.com/BenWent/HttpServer/blob/master/snapshot/%E8%AE%BE%E8%AE%A1%E5%9B%BE/%E4%B8%BB%E6%9C%8D%E5%8A%A1%E5%99%A8%E5%90%84%E6%BA%90%E7%A8%8B%E5%BA%8F%E4%B9%8B%E9%97%B4%E7%9A%84%E5%85%B3%E7%B3%BB.png](https://github.com/BenWent/HttpServer/blob/master/snapshot/设计图/主服务器各源程序之间的关系.png)>)

## slave_sever 中的程序依赖关系

![设计图](<[https://github.com/BenWent/HttpServer/blob/master/snapshot/%E8%AE%BE%E8%AE%A1%E5%9B%BE/%E4%BB%8E%E6%9C%8D%E5%8A%A1%E5%99%A8%E5%90%84%E6%BA%90%E7%A8%8B%E5%BA%8F%E4%B9%8B%E9%97%B4%E7%9A%84%E5%85%B3%E7%B3%BB.png](https://github.com/BenWent/HttpServer/blob/master/snapshot/设计图/从服务器各源程序之间的关系.png)>)

