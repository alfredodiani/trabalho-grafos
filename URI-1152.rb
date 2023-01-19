# 1152 - Dark Roads
# Challenge Link: https://www.beecrowd.com.br/judge/en/problems/view/1152
# Alfredo Diani

def maximum_daily_amount(n, m, edges)
  total = 0
  edges.each {|x, y, z| total += z}
  fa = Array.new(n) {|i| i}
  edges.sort_by! {|x, y, z| z}
  ans = 0
  save = 0
  edges.each do |x, y, z|
    x = find(x, fa)
    y = find(y, fa)
    if x != y
      fa[x] = y
      ans += 1
      save += z
      break if ans == n - 1
    end
  end
  total - save
end

def find(x, fa)
  return x if fa[x] == x
  fa[x] = find(fa[x], fa)
end

while (line = gets)
  n, m = line.split.map(&:to_i)
  break if n == 0 && m == 0
  edges = m.times.map { gets.split.map(&:to_i) }
  puts maximum_daily_amount(n, m, edges)
end
