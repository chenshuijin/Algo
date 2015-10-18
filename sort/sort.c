#include "sort.h"

/*
  a, the array
  start_ndx, the start index
  divid_ndx, the divide index
  end_ndx, the end index
*/
void divid_cmbine(int *a, int start_ndx, int divid_ndx, int end_ndx)
{
	int llen = divid_ndx - start_ndx + 1, rlen = end_ndx - divid_ndx;
	int *al, *ar;
	int i, j, k;

	if (llen == 0 || rlen == 0){ return; }

	al = (int *)malloc(sizeof(int)*llen);
	ar = (int *)malloc(sizeof(int)*rlen);

	i = 0;
	while (i < llen)
	{
		al[i] = a[start_ndx + i];
		i = i + 1;
	}
	i = 0;
	while (i < rlen){
		ar[i] = a[divid_ndx + 1 + i];
		i = i + 1;
	}
	
	i = 0, j = 0, k = start_ndx;
	while (k <= end_ndx){
		if (i >= llen)
		{
			a[k] = ar[j];
			j = j + 1;
			k = k + 1;
		}
		else if (j >= rlen)
		{
			a[k] = al[i];
			i = i + 1;
			k = k + 1;
		}
		else
		{
			if (al[i] < ar[j]){
				a[k] = al[i];
				i = i + 1;
				k = k + 1;
			}
			else
			{
				a[k] = ar[j];
				j = j + 1;
				k = k + 1;
			}
		}
	}
}

/*
a, the array
start_ndx, the start index
end_ndx, the end index
*/
void divid_cmbine_sort(int *a, int start_ndx, int end_ndx)
{
	int q;
	if (start_ndx < end_ndx){
		q = (start_ndx + end_ndx) / 2;
		divid_cmbine_sort(a, start_ndx, q);
		divid_cmbine_sort(a, q + 1, end_ndx);
		divid_cmbine(a, start_ndx, q, end_ndx);
	}
}