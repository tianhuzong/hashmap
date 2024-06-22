# HashMap

为python创建的hashmap

## 使用方法

### 安装
```bash
pip install thzhashmap
```

### 使用
```python
from hashmap import PyHashMap #please notice the package name
hmap = PyHashMap()
#插入
hmap.put("用户名","I am github cor edev")
hmap.put("密码","123456")

#查询
res = hmap.get("用户名")

#删除
hmap.remove("用户名")

#打印哈希表
hmap.print()
```

## 许可证
MIT

## 邮箱
tianhuzog@qq.com
