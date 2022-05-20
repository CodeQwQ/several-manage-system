import re
import bs4
import urllib.request
import xlwt

#主函数：
def main():
    url = "https://movie.douban.com/top250?start="
    html = askurl(url)   #获得源代码
    findinformation(html)   #找到自己想要的东西，然后保存到全局变量


#访问网页，获得源代码
def askurl(url):
    headers = {"User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/92.0.4515.107 Safari/537.36"}
    req = urllib.request.Request(url = url, headers = headers)
    response = urllib.request.urlopen(req)
    html = response.read().decode("utf-8")
    #print(html)
    return html


#查找数据
datalist = []
namecompile = re.compile(r'<span class="title">(.*?)</span>')
directcompile = re.compile(r'<p class="">(.*?)<br/>',re.S)

#以上为用到的查找方法以及全局变量
def findinformation(html):
    soup = bs4.BeautifulSoup(html, "html.parser")
    for item in soup.find_all("div", class_ = "item"):
        data = []
        # print(item)

       # print(type(item))     -----<class 'bs4.element.Tag'>
       #  break
        item = str(item)
        # 电影名字
        movie_name = re.findall(namecompile, item)[0]    #findall(patten, string)
        # print(movie_name)
        # break
        data.append(movie_name)

        # 电影导演
        movie_direct = re.findall(directcompile, item)
        print(movie_direct)
        break


if __name__ == '__main__':
    main()