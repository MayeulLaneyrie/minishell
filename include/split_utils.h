#ifndef SPLIT_UTILS_H
# define SPLIT_UTILS_H

/*
**	In split_utils.c
*/

/*
**	new_split mallocates data to a void ** of size n.
**	len is initialized to 0, as the split yet to be filled with data.
*/

t_split	*new_split(int n);

void	*del_split(t_split **split);

/*
**	list_to_split() and split_to_split() respectivelly convert a t_list to a
**	t_split and reciprocally. All the resources of the source structure are
**	freed, apart from the data they were holding.
*/

t_split	*list_to_split(t_list **lst);

t_list	*split_to_list(t_split **split);

#endif
