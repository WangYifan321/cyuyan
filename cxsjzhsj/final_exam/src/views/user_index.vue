<template>
  <div>
<h2 style="text-align: center;margin-top: 20px">杭电外来人员信息登记系统</h2>
<div v-if="$route.path === '/'" style="margin-top: 200px">
  <center>
  <el-button type="primary" @click="query()">我要查询</el-button>
  <br>
    <br>
    <br>
  <el-button type="primary" @click="form()">我要申请</el-button>
  </center>



</div>


<router-view></router-view>
  </div>
</template>

<script>
export default {
  name: "user_index",
  methods: {
    query(){
      this.$router.push('/query')
    },
    form(){
      this.$router.push('/form')
    }
  }
}
</script>

<style scoped>

</style>
