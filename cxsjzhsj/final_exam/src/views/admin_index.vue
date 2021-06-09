<template>
<el-container style="height: 100%; border: 1px solid #eee">

<el-container>
  <el-header style="text-align: right; font-size: 12px">
    <h1 style="float: left;margin-top: 0px;font-size: x-large">杭电外来人员后台管理系统</h1>
    <el-dropdown>
      <i class="el-icon-setting" style="margin-right: 15px"></i>
      <el-dropdown-menu slot="dropdown">
        <el-dropdown-item><el-link @click="queryByName()" :underline="false">按名字查询</el-link></el-dropdown-item>
        <el-dropdown-item><el-link @click="queryByDate()" :underline="false">按日期查询</el-link></el-dropdown-item>
        <el-dropdown-item>设置</el-dropdown-item>
      </el-dropdown-menu>
    </el-dropdown>
    <span>王小虎</span>
  </el-header>

  <el-main>
    <el-table :data="tableData">
      <el-table-column prop="name" label="姓名" width="140">
      </el-table-column>
      <el-table-column prop="phone" label="联系方式" width="120">
      </el-table-column>
      <el-table-column prop="gender" label="性别">
      </el-table-column>
      <el-table-column prop="guarantor_name" label="担保人姓名">
      </el-table-column>
      <el-table-column prop="apply_entry" label="申请进入时间">
      </el-table-column>
      <el-table-column prop="apply_leave" label="预计离开时间">
      </el-table-column>
      <el-table-column prop="affected" label="14天是否去过疫区">
      </el-table-column>
      <el-table-column prop="cough" label="是否有感冒发烧等症状">
      </el-table-column>
      <el-table-column prop="unit_info" label="单位信息">
      </el-table-column>
      <el-table-column prop="cause" label="申请事由">
      </el-table-column>
      <el-table-column  label="操作" prop="actual_entry">
        <template v-slot="scope">
          <el-button style="background-color: red;color: white;margin-left: 0px"  v-if="scope.row.actual_entry==='0001-01-01T00:00:00Z'">确认进校</el-button>
          <el-button style="background-color: #18516c;color: white;margin-left: 0px" v-else>确认离校</el-button>

        </template>


      </el-table-column>
    </el-table>
  </el-main>
</el-container>
</el-container>
</template>
<style>
.el-header {
  background-color: #B3C0D1;
  color: #333;
  line-height: 60px;
}

.el-aside {
  color: #333;
}
</style>

<script>
import {admin_get} from "../apis/api";
import {searchOutsiders} from "../apis/api";
import row from "element-ui/packages/row/src/row";

export default {
  name: 'admin_index',
  data() {
    const item = {
      date1: '2016-05-02 21:21:32',
      date2: '2017-09-13 21:18:21',
      gender: '男',
      phone: '12322214568',
      id_card: '71892891716227161721',
      guarantor_name: '哈哈',
      affected: '否',
      cough: '否',
      health_code: '绿',
      unit_info: '杭电',
      cause: '吃饭啊',
      name: '王小虎'

    };
    return {
      tableData: []
    }
  },
  methods: {
    queryByName(){
      this.$prompt('请输入您要查询的姓名', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消'
      }).then(({ value }) => {
        this.$message({
          type: 'success',
          message: '查询' + value +'成功'
        });
        let url = '/apis/outsiders/search?name='+value
        let params = {}
        searchOutsiders(url,params).then(res=>{
          alert("?")
          this.tableData =  res
        })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '取消输入'
        });
      });
    },
    queryByDate(){
      this.$prompt('请输入您要查询的日期,若为日期区间以’|’ 分割', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        inputPlaceholder: '日期格式为yyyy-MM-dd HH:mm:ss'
      }).then(({ value }) => {
        this.$message({
          type: 'success',
          message: '查询' + value +'成功'
        });
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '取消输入'
        });
      });
    },
    entry() {
       "asd".length
    },
    table(){
      let params = {}
      admin_get(params).then(res => {
        this.tableData = res

      })
    }
  },
  mounted() {
    this.table()
  }
};
</script>
