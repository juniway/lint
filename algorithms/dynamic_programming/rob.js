let counter = 0;

function houseRobberRecursive(arr) {
  function stealFromHouse(index) {
    if (index >= arr.length) {
      counter++;
      return 0;
    }
    return Math.max(
      arr[index] + stealFromHouse(index + 2),
      stealFromHouse(index + 1)
    );
  }
  return stealFromHouse(0);
}

// console.log(houseRobberRecursive([3, 1, 2, 5, 4, 2, 5]))
// houseRobberRecursive([1, 2, 3, 4])
// console.log(counter)

let results = {};
let array = [];

for (let i = 0; i <= 20; i++) {
  houseRobberRecursive(array);
  results[i] = counter;
  counter = 0;
  array.push(i);
}

function houseRobber(houses) {
  let max_gold = [];
  max_gold[0] = 0;
  max_gold[1] = houses[0];
  for (let i = 2; i < houses.length; i++) {
    let twoBack = max_gold[i - 2] || 0;
    let oneBack = max_gold[i - 1] || 0;
    max_gold.push(Math.max(houses[i] + twoBack, oneBack));
  }

  return max_gold;
}

function houseRobber2(houses) {
  let currentMax = 0;
  let prevMax = 0;

  for (let i = 0; i < houses.length; i++) {
    let currentHouse = houses[i];
    let newMax = Math.max(currentMax, prevMax + currentHouse);
    prevMax = currentMax;
    currentMax = newMax;
  }

  return currentMax;
}

console.log(houseRobber([3, 5, 1, 3, 4, 5, 1]));
